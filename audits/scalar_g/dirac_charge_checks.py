"""Gauge/charge gates for the pinned UBT real-linear Dirac candidate.

These checks assume commuting real Theta coordinates and a chosen right frame.
They do not select a UBT Hamiltonian, connection, physical quotient, or statistics.
"""

import cmath
import random
import unittest

import sympy as s


I = s.I
SX = s.Matrix([[0, 1], [1, 0]])
SY = s.Matrix([[0, -I], [I, 0]])
SZ = s.diag(1, -1)
EPSILON = s.Matrix([[0, 1], [-1, 0]])
X = s.Matrix(s.symbols("x0:8", real=True))
PHI = s.Symbol("phi", real=True)
J2 = s.Matrix([[0, -1], [1, 0]])
J8 = s.diag(J2, J2, J2, J2)


def theta(x):
    return s.Matrix([[x[0] + I * x[1], x[4] + I * x[5]],
                     [x[2] + I * x[3], x[6] + I * x[7]]])


def weyl(matrix):
    return matrix[:, 0].col_join(EPSILON * matrix[:, 1].conjugate())


def realify(vector):
    return s.Matrix([part for z in vector for part in s.expand_complex(z).as_real_imag()])


THETA = theta(X)
U = weyl(THETA)
Q = realify(U).jacobian(X)
OMEGA = Q.T * J8 * Q
AXIAL = s.diag(1, 1, -1, -1)
RIGHT_PHASE = s.diag(s.exp(I * PHI), s.exp(-I * PHI))
RIGHT_GENERATOR = s.diag(J2, J2, -J2, -J2)
MASS = s.Symbol("m", real=True)
P1, P2, P3 = s.symbols("p1 p2 p3", real=True)
SIGMA_P = P1 * SX + P2 * SY + P3 * SZ
H = (-SIGMA_P).row_join(MASS * s.eye(2)).col_join((MASS * s.eye(2)).row_join(SIGMA_P))


class DiracChargeChecks(unittest.TestCase):
    def zero(self, expression):
        entries = expression if isinstance(expression, s.MatrixBase) else [expression]
        for entry in entries:
            self.assertEqual(s.simplify(s.expand(entry.rewrite(s.exp))), 0)

    def test_01_real_linear_map_is_invertible_and_norm_preserving(self):
        self.zero(Q.T * Q - s.eye(8))
        self.zero(OMEGA + OMEGA.T)
        self.assertEqual(OMEGA.det(), 1)

    def test_02_central_phase_is_axial_after_the_map(self):
        chiral_phase = s.diag(s.exp(I * PHI), s.exp(I * PHI),
                             s.exp(-I * PHI), s.exp(-I * PHI))
        self.zero(weyl(s.exp(I * PHI) * THETA) - chiral_phase * U)

    def test_03_vector_phase_pulls_back_to_traceless_right_phase(self):
        self.zero(weyl(THETA * RIGHT_PHASE) - s.exp(I * PHI) * U)
        self.zero(RIGHT_PHASE.det() - 1)
        self.zero(RIGHT_PHASE.H * RIGHT_PHASE - s.eye(2))

    def test_04_mass_breaks_axial_but_not_vector_phase(self):
        commutator = H * AXIAL - AXIAL * H
        expected = s.zeros(2).row_join(-2 * MASS * s.eye(2)).col_join(
            (2 * MASS * s.eye(2)).row_join(s.zeros(2)))
        self.zero(commutator - expected)
        self.zero(commutator.subs(MASS, 0))
        self.zero(H * s.eye(4) - s.eye(4) * H)
        self.assertNotEqual(commutator.subs(MASS, 1), s.zeros(4))

    def test_05_explicit_axial_charge_nonconservation_witness(self):
        u = s.Matrix([1, 0, I, 0])  # deliberately unnormalized
        derivative = (I * u.H * (H * AXIAL - AXIAL * H) * u)[0]
        self.zero(derivative - 4 * MASS)

    def test_06_central_and_electric_moment_maps_are_different(self):
        # iota_(K x) Omega = d mu implies Hessian(mu) = -Omega K.
        central_hessian = -OMEGA * J8
        electric_hessian = -OMEGA * RIGHT_GENERATOR
        self.zero(central_hessian - s.diag(1, 1, 1, 1, -1, -1, -1, -1))
        self.zero(electric_hessian - s.eye(8))
        self.zero((X.T * electric_hessian * X)[0] / 2 - sum(x ** 2 for x in X) / 2)
        self.assertNotEqual(central_hessian, electric_hessian)

    def test_07_both_phase_actions_are_symplectic(self):
        for generator in (J8, RIGHT_GENERATOR):
            self.zero(generator.T * OMEGA + OMEGA * generator)

    def test_08_zero_level_moment_map_has_positive_definite_quadratic_form(self):
        mu = sum(x ** 2 for x in X) / 2
        self.zero(s.hessian(mu, X) - s.eye(8))
        self.zero(mu.subs(dict.fromkeys(X, 0)))
        # The conclusion mu=0 iff x=0 additionally uses that all x are real.
        self.assertTrue(all(x.is_real for x in X))

    def test_09_canonical_sharp_anticommutator(self):
        basis = (I * s.eye(2), -I * SX, -I * SY, -I * SZ)
        for a in range(4):
            for b in range(4):
                expected = (-1 if a == 0 else 1) * s.eye(2) if a == b else s.zeros(2)
                self.zero((basis[a].adjugate() * basis[b] + basis[b].adjugate() * basis[a]) / 2 - expected)

    def test_10_general_right_factor_rescales_metric_by_its_determinant(self):
        entries = s.symbols("a0:12")
        e, f, r = (s.Matrix(2, 2, entries[start:start + 4]) for start in (0, 4, 8))
        original = (e.adjugate() * f + f.adjugate() * e) / 2
        transformed = ((e * r).adjugate() * f * r + (f * r).adjugate() * e * r) / 2
        self.zero(transformed - r.det() * original)

    def test_11_electric_right_phase_preserves_metric_but_not_the_real_slice(self):
        e0 = I * s.eye(2)
        transformed = e0 * RIGHT_PHASE
        self.zero(transformed.adjugate() * transformed + s.eye(2))
        self.zero(transformed + transformed.H - s.diag(-2 * s.sin(PHI), 2 * s.sin(PHI)))
        self.assertNotEqual((transformed + transformed.H).subs(PHI, s.pi / 2), s.zeros(2))

    def test_12_all_slice_preserving_right_factors_are_real_scalars(self):
        parameters = s.symbols("r0:8", real=True)
        r = s.Matrix([[parameters[0] + I * parameters[1], parameters[2] + I * parameters[3]],
                      [parameters[4] + I * parameters[5], parameters[6] + I * parameters[7]]])
        equations = []
        for basis in (I * s.eye(2), -I * SX, -I * SY, -I * SZ):
            for entry in basis * r + (basis * r).H:
                equations.extend(s.expand_complex(entry).as_real_imag())
        coefficients, _ = s.linear_eq_to_matrix(equations, parameters)
        expected = s.Matrix([1, 0, 0, 0, 0, 0, 1, 0])
        self.assertEqual(coefficients.rank(), 7)
        self.assertEqual(coefficients.nullspace(), [expected])
        scalar = s.Symbol("r", real=True)
        self.zero((scalar * s.eye(2)).det() - scalar ** 2)
        self.assertEqual(set(s.solve(scalar ** 2 - 1, scalar)), {-1, 1})

    def test_13_right_column_axis_is_not_invariant_under_right_frame_mixing(self):
        frame = s.Matrix([[1, 1], [-1, 1]]) / s.sqrt(2)
        self.zero(frame.H * frame - s.eye(2))
        self.zero(frame.inv() * SZ * frame - SX)
        self.assertNotEqual(SX, SZ)

    def test_14_independent_python_complex_phase_and_charge_checks(self):
        # No SymPy expressions or matrix routines enter this numerical channel.
        rng = random.Random(20261024)
        for _ in range(50):
            psi = [complex(rng.uniform(-2, 2), rng.uniform(-2, 2)) for _ in range(2)]
            chi = [complex(rng.uniform(-2, 2), rng.uniform(-2, 2)) for _ in range(2)]
            u = psi + [chi[1].conjugate(), -chi[0].conjugate()]
            phase = cmath.exp(1j * rng.uniform(-3, 3))
            central_chi = [phase * z for z in chi]
            central_u = [phase * z for z in psi] + [central_chi[1].conjugate(), -central_chi[0].conjugate()]
            right_chi = [z / phase for z in chi]
            right_u = [phase * z for z in psi] + [right_chi[1].conjugate(), -right_chi[0].conjugate()]
            for i in range(4):
                expected = (phase if i < 2 else phase.conjugate()) * u[i]
                self.assertLess(abs(central_u[i] - expected), 1e-12)
                self.assertLess(abs(right_u[i] - phase * u[i]), 1e-12)
            px, py, pz, mass = [rng.uniform(-2, 2) for _ in range(4)]
            hu = [-pz * u[0] - (px - 1j * py) * u[1] + mass * u[2],
                  -(px + 1j * py) * u[0] + pz * u[1] + mass * u[3],
                  mass * u[0] + pz * u[2] + (px - 1j * py) * u[3],
                  mass * u[1] + (px + 1j * py) * u[2] - pz * u[3]]
            rates = [2 * (u[i].conjugate() * (-1j * hu[i])).real for i in range(4)]
            mixing = u[0].conjugate() * u[2] + u[1].conjugate() * u[3]
            self.assertLess(abs(sum(rates)), 1e-11)
            self.assertLess(abs(rates[0] + rates[1] - rates[2] - rates[3] - 4 * mass * mixing.imag), 1e-11)


if __name__ == "__main__":
    unittest.main()
