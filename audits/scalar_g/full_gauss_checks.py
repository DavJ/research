"""Conditional Gauss/boundary and commuting-Dirac energy benchmarks.

The independent Maxwell pair is a comparator, not a derived UBT field.
Exact SymPy checks and independent standard-library numerical channels.
"""
import cmath
import math
import random
import unittest

import sympy as s


J2 = s.Matrix([[0, -1], [1, 0]])
OMEGA = s.diag(J2, J2, -J2, -J2)
r, L, Q, m, k = s.symbols("r L Q m k", positive=True)
radius_ratio = r / L
rho = Q * s.exp(-radius_ratio**2) / (s.pi**s.Rational(3, 2) * L**3)
enclosed = Q * (s.erf(radius_ratio) - 2 * radius_ratio * s.exp(-radius_ratio**2) / s.sqrt(s.pi))
flux_radial = enclosed / (4 * s.pi * r**2)
potential = Q * s.erf(radius_ratio) / (4 * s.pi * r)
field_energy = Q**2 / (4 * s.sqrt(2) * s.pi**s.Rational(3, 2) * L)
energy = s.sqrt(k**2 + m**2)
sigma3 = s.diag(1, -1)
HD = s.BlockMatrix([[-k * sigma3, m * s.eye(2)], [m * s.eye(2), k * sigma3]]).as_explicit()
negative_vector = s.Matrix([m, 0, k - energy, 0])
normalization = s.sqrt(m**2 + (k - energy)**2)
negative_unit = negative_vector / normalization


class GaussGeneratorChecks(unittest.TestCase):
    def test_phase_generator_with_stated_hamiltonian_sign(self):
        # i_X omega = -dH, so Hess(H)=Omega K. Gauge phase is exp(-i alpha).
        generator = -OMEGA
        self.assertEqual(OMEGA * generator, s.eye(8))
        x = s.Matrix(s.symbols("x0:8", real=True))
        self.assertEqual(s.expand((x.T * generator * x)[0]), 0)

    def test_bulk_boundary_contraction_by_integration(self):
        # Nonzero endpoint alpha tests the surface term rather than dropping it.
        z = s.symbols("z", real=True)
        alpha, delta_pi, delta_rho = z**2 + 1, z**3 - 2*z + 1, z + 3
        contraction = s.integrate(-alpha*delta_rho - s.diff(alpha,z)*delta_pi, (z,0,1))
        delta_bulk = s.integrate(alpha*(delta_rho-s.diff(delta_pi,z)), (z,0,1))
        delta_surface = (alpha*delta_pi).subs(z,1)-(alpha*delta_pi).subs(z,0)
        self.assertEqual(s.simplify(contraction+delta_bulk+delta_surface), 0)
        self.assertNotEqual(delta_surface, 0)

    def test_minimal_covariant_momentum_gauge_law(self):
        z = s.symbols("z", real=True)
        phase, amplitude, connection = s.Function("a")(z), s.Function("f")(z), s.Function("A")(z)
        rotated = s.exp(-s.I*phase)*amplitude
        transformed = -s.I*s.diff(rotated,z)+(connection+s.diff(phase,z))*rotated
        original = s.exp(-s.I*phase)*(-s.I*s.diff(amplitude,z)+connection*amplitude)
        self.assertEqual(s.simplify(transformed-original), 0)

    def test_gauss_density_is_abelian_phase_invariant(self):
        x = s.Matrix(s.symbols("x0:8", real=True))
        self.assertEqual((x.T * OMEGA * x)[0].expand(), 0)
        # The flux momentum is invariant and no A occurs in C=rho-div Pi.
        self.assertEqual(OMEGA.T, -OMEGA)
        # Also check C-dot=0 from the coupled comparator, not only phase invariance.
        real = s.Matrix(s.symbols("a0:4", real=True))
        imag = s.Matrix(s.symbols("b0:4", real=True))
        u = real + s.I*imag
        gradients = [s.Matrix(s.symbols(f"d{axis}a0:4", real=True))
                     +s.I*s.Matrix(s.symbols(f"d{axis}b0:4", real=True)) for axis in range(3)]
        pauli = [s.Matrix([[0,1],[1,0]]),s.Matrix([[0,-s.I],[s.I,0]]),sigma3]
        alpha = [s.diag(-matrix,matrix) for matrix in pauli]
        beta = s.BlockMatrix([[s.zeros(2),s.eye(2)],[s.eye(2),s.zeros(2)]]).as_explicit()
        potential = s.symbols("A0 A1 A2 V", real=True)
        du = -sum((a*g for a,g in zip(alpha,gradients)),s.zeros(4,1))
        du -= s.I*(m*beta+sum((potential[i]*alpha[i] for i in range(3)),s.zeros(4))
                     +potential[3]*s.eye(4))*u
        rho_dot = (du.conjugate().T*u+u.conjugate().T*du)[0]/2
        div_current = sum((g.conjugate().T*a*u+u.conjugate().T*a*g)[0]/2
                          for a,g in zip(alpha,gradients))
        self.assertEqual(s.expand(rho_dot+div_current), 0)


class GaussianFluxChecks(unittest.TestCase):
    def test_total_charge_normalization(self):
        self.assertEqual(s.integrate(4*s.pi*r*r*rho,(r,0,s.oo)), Q)

    def test_radial_gauss_equation(self):
        divergence = s.diff(r*r*flux_radial,r)/(r*r)
        self.assertEqual(s.simplify(divergence-rho), 0)

    def test_smooth_cartesian_origin(self):
        self.assertEqual(s.limit(flux_radial/r,r,0,dir="+"), Q/(3*s.pi**s.Rational(3,2)*L**3))

    def test_decay_does_not_force_zero_surface_charge(self):
        self.assertEqual(s.limit(flux_radial,r,s.oo), 0)
        self.assertEqual(s.limit(4*s.pi*r*r*flux_radial,r,s.oo), Q)

    def test_potential_gradient(self):
        self.assertEqual(s.simplify(-s.diff(potential,r)-flux_radial), 0)

    def test_energy_from_charge_potential(self):
        value = s.integrate(2*s.pi*r*r*rho*potential,(r,0,s.oo))
        self.assertEqual(s.simplify(value-field_energy), 0)

    def test_energy_from_fourier_gaussian(self):
        momentum = s.symbols("p",positive=True)
        value = Q**2/(4*s.pi**2)*s.integrate(s.exp(-L*L*momentum*momentum/2),(momentum,0,s.oo))
        self.assertEqual(s.simplify(value-field_energy), 0)


class ConstrainedDiracEnergyChecks(unittest.TestCase):
    def test_negative_mass_shell_and_normalization(self):
        self.assertEqual(s.simplify(HD*negative_vector+energy*negative_vector), s.zeros(4,1))
        self.assertEqual(s.simplify((negative_unit.T*negative_unit)[0]), 1)

    def test_dirac_symbol_square(self):
        self.assertEqual(HD*HD-(k*k+m*m)*s.eye(4), s.zeros(4))

    def test_gaussian_spinor_has_fixed_charge(self):
        envelope_squared = 2*rho
        density = s.simplify(envelope_squared*(negative_unit.T*negative_unit)[0]/2)
        self.assertEqual(s.simplify(density-rho), 0)

    def test_envelope_derivative_integrates_to_zero(self):
        z = s.symbols("z",real=True)
        f = s.exp(-z*z/(2*L*L))
        self.assertEqual(s.integrate(f*s.diff(f,z),(z,-s.oo,s.oo)), 0)

    def test_energy_of_fixed_charge_data_is_unbounded(self):
        total = -Q*energy+field_energy
        self.assertEqual(s.limit(total,k,s.oo), -s.oo)
        self.assertEqual(s.simplify(s.diff(total,k)+Q*k/energy), 0)


def _simpson(function, upper, intervals=4096):
    step = upper / intervals
    return step/3 * (function(0)+function(upper)
        +4*sum(function(i*step) for i in range(1,intervals,2))
        +2*sum(function(i*step) for i in range(2,intervals,2)))


class IndependentNumericalChannels(unittest.TestCase):
    def test_direct_dirac_eigenvectors_without_cas(self):
        rng = random.Random(20261025)
        for _ in range(50):
            mass, momentum = rng.uniform(.2,3), rng.uniform(.1,10)
            level = math.hypot(mass,momentum)
            # Avoid cancellation for the second component.
            a,b = mass,-mass*mass/(momentum+level)
            norm = math.hypot(a,b)
            v = [a/norm,0j,b/norm,0j]
            hv = [-momentum*v[0]+mass*v[2], momentum*v[1]+mass*v[3],
                  mass*v[0]+momentum*v[2],mass*v[1]-momentum*v[3]]
            self.assertLess(max(abs(hv[i]+level*v[i]) for i in range(4)),1e-11)
            self.assertAlmostEqual(sum(abs(x)**2 for x in v),1.0,places=12)
            for phase in [.3,1.7]:
                rotated = [cmath.exp(1j*phase)*x for x in v]
                self.assertAlmostEqual(sum(abs(x)**2 for x in rotated),1.0,places=12)

    def test_direct_electric_energy_quadrature_with_coulomb_tail(self):
        # Dimensionless r/L, Q=L=1. Exact analytic tail beyond 12 up to exp(-144).
        def integrand(t):
            if t == 0:
                return 0.0
            charge = math.erf(t)-2*t*math.exp(-t*t)/math.sqrt(math.pi)
            return charge*charge/(8*math.pi*t*t)
        numerical = _simpson(integrand,12.0)+1/(8*math.pi*12.0)
        exact = 1/(4*math.sqrt(2)*math.pi**1.5)
        self.assertAlmostEqual(numerical,exact,places=10)

    def test_large_radius_flux_and_fixed_charge_energy_family(self):
        flux = lambda t: math.erf(t)-2*t*math.exp(-t*t)/math.sqrt(math.pi)
        self.assertAlmostEqual(flux(10),1.0,places=12)
        self.assertAlmostEqual(flux(20),1.0,places=12)
        electric = 1/(4*math.sqrt(2)*math.pi**1.5)
        values = [-math.hypot(p,1)+electric for p in [1,10,100]]
        self.assertGreater(values[0],values[1])
        self.assertGreater(values[1],values[2])


if __name__ == "__main__":
    unittest.main()
