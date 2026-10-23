"""Exact checks accompanying README.md; not a proof of a physical theory.

Run from the repository root:
    python -B audits/scalar_g/audit_checks.py -v

Historical equations are transcribed explicitly, not parsed from TeX. Their
source hashes are checked so a changed convention requires a new review.
"""

import hashlib
import json
from pathlib import Path
import unittest

import sympy as s


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
HALF = s.Rational(1, 2)
I = s.I
BASIS = (
    s.eye(2),
    s.Matrix([[I, 0], [0, -I]]),
    s.Matrix([[0, 1], [-1, 0]]),
    s.Matrix([[0, I], [I, 0]]),
)


def qmatrix(q):
    return sum((coefficient * basis for coefficient, basis in zip(q, BASIS)), s.zeros(2))


def qproduct(q, r):
    a, v = q[0], s.Matrix(q[1:])
    b, w = r[0], s.Matrix(r[1:])
    return s.Matrix([a * b - v.dot(w), *(a * w + b * v + v.cross(w))])


def dagger(q):
    """Quaternion conjugation followed by coefficient complex conjugation."""
    return s.Matrix([s.conjugate(q[0]), *(-s.conjugate(c) for c in q[1:])])


T, X, Y, Z = COORDS = s.symbols("t x y z", real=True)
ETA = (1, -1, -1, -1)
LAMBDA = s.Symbol("lambda", real=True)
A = tuple(s.Function(f"A_{nu}")(*COORDS) for nu in range(4))  # covariant components
J = tuple(s.Function(f"J^{nu}")(*COORDS) for nu in range(4))  # contravariant components
F = s.Matrix(4, 4, lambda mu, nu: s.diff(A[nu], COORDS[mu]) - s.diff(A[mu], COORDS[nu]))
G = sum(ETA[mu] * s.diff(A[mu], COORDS[mu]) for mu in range(4))
F_SQUARED = sum(ETA[mu] * ETA[nu] * F[mu, nu] ** 2 for mu in range(4) for nu in range(4))
ACTION_DENSITY = -F_SQUARED / 4 + LAMBDA * G ** 2 / 2 - sum(J[nu] * A[nu] for nu in range(4))


def box(expression):
    return sum(ETA[mu] * s.diff(expression, COORDS[mu], 2) for mu in range(4))


def euler_lagrange(nu):
    return s.expand(
        s.diff(ACTION_DENSITY, A[nu])
        - sum(s.diff(s.diff(ACTION_DENSITY, s.diff(A[nu], COORDS[mu])), COORDS[mu]) for mu in range(4))
    )


def phase_space():
    """Independent velocities, momenta and spatial first derivatives of A_mu."""
    v = s.Matrix(s.symbols("v0:4", real=True))
    p = s.Matrix(s.symbols("p0:4", real=True))
    d = s.Matrix(3, 4, s.symbols("d0:12", real=True))
    div_a = sum(d[i, i + 1] for i in range(3))
    magnetic = sum((d[i, j + 1] - d[j, i + 1]) ** 2 for i in range(3) for j in range(i + 1, 3)) / 2
    electric = sum((v[i + 1] - d[i, 0]) ** 2 for i in range(3)) / 2
    lagrangian = electric - magnetic + LAMBDA * (v[0] - div_a) ** 2 / 2
    hamiltonian = (
        sum(p[i + 1] ** 2 for i in range(3)) / 2 + magnetic
        + sum(p[i + 1] * d[i, 0] for i in range(3))
        + p[0] * div_a + p[0] ** 2 / (2 * LAMBDA)
    )
    return v, p, d, lagrangian, hamiltonian


class ExactChecks(unittest.TestCase):
    def zero(self, expression):
        if isinstance(expression, s.MatrixBase):
            for entry in expression:
                self.assertEqual(s.simplify(s.expand(entry)), 0)
        else:
            self.assertEqual(s.simplify(s.expand(expression)), 0)

    def test_01_historical_source_hashes(self):
        manifest = json.loads((HERE / "source_manifest.json").read_text())
        self.assertEqual(manifest["base_commit"], "eb22e826d26e6a10fc5905aef6cda43428cd4d24")
        for path, digest in manifest["sha256"].items():
            with self.subTest(path=path):
                self.assertEqual(hashlib.sha256((ROOT / path).read_bytes()).hexdigest(), digest)

    def test_02_quaternion_product_against_independent_pauli_matrices(self):
        q = s.Matrix(s.symbols("q0:4", complex=True))
        r = s.Matrix(s.symbols("r0:4", complex=True))
        self.zero(qmatrix(qproduct(q, r)) - qmatrix(q) * qmatrix(r))
        for basis in BASIS[1:]:
            self.zero(basis * basis + s.eye(2))

    def test_03_gradient_potential_decomposition(self):
        d = s.Matrix(4, 4, s.symbols("d0:16", real=True))
        weights = (1, I, I, I)
        actual = sum((weights[mu] * weights[nu] * d[mu, nu] * BASIS[mu] * BASIS[nu]
                      for mu in range(4) for nu in range(4)), s.zeros(2))
        expected = s.Matrix([
            s.trace(d),
            I * (d[0, 1] + d[1, 0]) - d[2, 3] + d[3, 2],
            I * (d[0, 2] + d[2, 0]) + d[1, 3] - d[3, 1],
            I * (d[0, 3] + d[3, 0]) - d[1, 2] + d[2, 1],
        ])
        self.zero(actual - qmatrix(expected))

    def test_04_full_complex_G_energy_expansion(self):
        gr, gi = s.symbols("g_R g_I", real=True)
        b = s.Matrix(s.symbols("B1:4", real=True))
        e = s.Matrix(s.symbols("e1:4", real=True))  # e = E/c
        q = s.Matrix([gr + I * gi, *(-b - I * e)])
        actual = -qproduct(q, dagger(q)) / 2  # mu = 1
        expected = s.Matrix([
            -(gr ** 2 + gi ** 2 + b.dot(b) + e.dot(e)) / 2,
            *(I * gr * e - I * gi * b - I * b.cross(e)),
        ])
        self.zero(actual - expected)
        self.zero(qmatrix(actual) + qmatrix(q) * qmatrix(q).H / 2)

    def test_05_pure_magnetic_counterexample(self):
        q = s.Matrix([0, -1, 0, 0])
        actual = -qproduct(q, dagger(q))[0] / 2
        self.assertEqual(actual, -HALF)
        self.assertNotEqual(actual, HALF)  # historical expanded energy

    def test_06_pure_electric_counterexample(self):
        q = s.Matrix([0, -I, 0, 0])
        self.assertEqual(-qproduct(q, dagger(q))[0] / 2, -HALF)

    def test_07_one_global_sign_cannot_reproduce_mixed_energy(self):
        gr, b, e = s.symbols("g B e", real=True)
        scalar_product = qproduct(s.Matrix([gr, -b - I * e, 0, 0]), s.Matrix([gr, b - I * e, 0, 0]))[0]
        historical = (-gr ** 2 + b ** 2 + e ** 2) / 2
        for sign in (-1, 1):
            self.assertNotEqual(s.expand(sign * scalar_product / 2 - historical), 0)

    def test_08_projected_maxwell_energy_and_poynting_vector(self):
        b = s.Matrix(s.symbols("B1:4", real=True))
        e = s.Matrix(s.symbols("E1:4", real=True))  # c = mu = 1
        p = s.Matrix([0, *(-b - I * e)])
        product = qproduct(p, dagger(p)) / 2
        self.zero(product[0] - (b.dot(b) + e.dot(e)) / 2)
        self.zero(s.Matrix(product[1:]) + I * e.cross(b))

    def test_09_maxwell_stress_tensor_00(self):
        t00 = -sum(ETA[rho] * (ETA[0] * ETA[rho] * F[0, rho]) ** 2 for rho in range(4)) + F_SQUARED / 4
        expected = sum(F[0, i] ** 2 for i in range(1, 4)) / 2 + sum(F[i, j] ** 2 for i in range(1, 4) for j in range(i + 1, 4)) / 2
        self.zero(t00 - expected)

    def test_10_gauge_transformation_for_arbitrary_smooth_potentials(self):
        chi = s.Function("chi")(*COORDS)
        phi = s.Function("phi")(*COORDS)
        a = s.Matrix([s.Function(f"a{i}")(*COORDS) for i in range(3)])
        spatial = COORDS[1:]
        shifted_phi = phi - s.diff(chi, T)
        shifted_a = a + s.Matrix([s.diff(chi, x) for x in spatial])
        for i, x in enumerate(spatial):
            self.zero(-s.diff(shifted_phi, x) - s.diff(shifted_a[i], T) + s.diff(phi, x) + s.diff(a[i], T))
        for i, j in ((0, 1), (1, 2), (2, 0)):
            self.zero(s.diff(shifted_a[j] - a[j], spatial[i]) - s.diff(shifted_a[i] - a[i], spatial[j]))
        original_g = s.diff(phi, T) + sum(s.diff(a[i], spatial[i]) for i in range(3))
        shifted_g = s.diff(shifted_phi, T) + sum(s.diff(shifted_a[i], spatial[i]) for i in range(3))
        self.zero(shifted_g - original_g + box(chi))

    def test_11_spatially_decaying_pure_gauge_has_finite_nonzero_G_norm(self):
        amplitude = s.Symbol("a", real=True)
        length, radius = s.symbols("L r", positive=True)
        r2 = X ** 2 + Y ** 2 + Z ** 2
        chi = amplitude * s.exp(-r2 / length ** 2)
        laplacian = sum(s.diff(chi, x, 2) for x in COORDS[1:])
        expected = amplitude * (4 * r2 / length ** 4 - 6 / length ** 2) * s.exp(-r2 / length ** 2)
        self.zero(laplacian - expected)
        radial_g = amplitude * (4 * radius ** 2 / length ** 4 - 6 / length ** 2) * s.exp(-radius ** 2 / length ** 2)
        norm = s.integrate(4 * s.pi * radius ** 2 * radial_g ** 2, (radius, 0, s.oo))
        self.zero(norm - 15 * s.pi ** s.Rational(3, 2) * amplitude ** 2 / (2 * s.sqrt(2) * length))

    def test_12_quadratic_invariant_boundary_identity(self):
        i1 = sum(ETA[mu] * ETA[nu] * s.diff(A[nu], COORDS[mu]) ** 2 for mu in range(4) for nu in range(4))
        i2 = sum(ETA[mu] * ETA[nu] * s.diff(A[nu], COORDS[mu]) * s.diff(A[mu], COORDS[nu]) for mu in range(4) for nu in range(4))
        current = [sum(A[nu] * ETA[nu] * ETA[mu] * s.diff(A[mu], COORDS[nu]) for nu in range(4)) - ETA[mu] * A[mu] * G for mu in range(4)]
        self.zero(F_SQUARED - 2 * (i1 - i2))
        self.zero(i2 - G ** 2 - sum(s.diff(current[mu], COORDS[mu]) for mu in range(4)))

    def test_13_euler_lagrange_equations(self):
        for nu in range(4):
            expected = sum(s.diff(ETA[mu] * ETA[nu] * F[mu, nu], COORDS[mu]) for mu in range(4)) - LAMBDA * ETA[nu] * s.diff(G, COORDS[nu]) - J[nu]
            self.zero(euler_lagrange(nu) - expected)

    def test_14_divergence_and_current_conservation_identity(self):
        divergence = sum(s.diff(euler_lagrange(nu), COORDS[nu]) for nu in range(4))
        self.zero(divergence + LAMBDA * box(G) + sum(s.diff(J[nu], COORDS[nu]) for nu in range(4)))

    def test_15_velocity_hessian_and_maxwell_degeneracy(self):
        v, _, _, lagrangian, _ = phase_space()
        hessian = s.hessian(lagrangian, v)
        self.zero(hessian - s.diag(LAMBDA, 1, 1, 1))
        self.zero(hessian.det() - LAMBDA)
        self.assertEqual(hessian.subs(LAMBDA, 0).rank(), 3)

    def test_16_canonical_momenta_and_exact_legendre_transform(self):
        v, p, d, lagrangian, expected = phase_space()
        velocities = {v[0]: p[0] / LAMBDA + sum(d[i, i + 1] for i in range(3))}
        velocities.update({v[i + 1]: p[i + 1] + d[i, 0] for i in range(3)})
        for nu in range(4):
            self.zero(s.diff(lagrangian, v[nu]).subs(velocities) - p[nu])
        actual = (p.dot(v) - lagrangian).subs(velocities)
        self.zero(actual - expected)  # identity on lambda != 0

    def test_17_negative_lambda_has_negative_kinetic_direction(self):
        _, p, d, _, h = phase_space()
        substitution = {entry: 0 for entry in d}
        substitution.update({p[i]: 0 for i in range(1, 4)})
        self.zero(h.subs(substitution) - p[0] ** 2 / (2 * LAMBDA))

    def test_18_positive_lambda_has_negative_longitudinal_direction(self):
        _, p, d, _, h = phase_space()
        gradients = s.symbols("f_x f_y f_z", real=True)
        substitution = {entry: 0 for entry in d}
        substitution.update({d[i, 0]: gradients[i] for i in range(3)})
        substitution.update({p[i + 1]: -gradients[i] for i in range(3)})
        substitution[p[0]] = 0
        self.zero(h.subs(substitution, simultaneous=True) + sum(g ** 2 for g in gradients) / 2)


if __name__ == "__main__":
    unittest.main()
