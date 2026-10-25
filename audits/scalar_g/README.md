# Scalar G and energy: audit of the historical model

Date: 2026-10-23. Historical source: `eb22e826d26e6a10fc5905aef6cda43428cd4d24`.

**Result:** the potential-gradient identity is correct, but the historical energy
definition and its expanded formula disagree. The defined scalar G is gauge
dependent in Maxwell theory. Promoting its square to a physical term in the
restricted single-vector action below gives an unbounded Hamiltonian unless
additional physical restrictions are supplied. No beyond-Maxwell prediction has
been obtained from the audited premises.

**Česky:** Základní kvaternionový rozvoj sedí. Znaménka energie však nesouhlasí
s její definicí a samotné G není kalibračně nezávislá měřitelná veličina. Prověřili
jsme i nejjednodušší pokus o vlastní dynamiku G; bez dalších vazeb má neomezenou
energii. Tento výsledek uzavírá uvedený jednoduchý mechanismus, nikoli všechny
možné skalární teorie nebo současnou samostatnou UBT.

## Scope and reproduction

The 2026-10-24 continuation compares the newer UBT Dirac candidate with charge,
coframe and gauge-constraint requirements: [English](ubt_dirac_charge_gate.en.md)
and [Czech](ubt_dirac_charge_gate.cs.md). Its 14 checks supplement the 18 original
checks here; the result does not promote that candidate to a selected theory.

The original `.tex`, `.wxm`, and image sources remain unchanged. Their SHA-256
hashes are in [source_manifest.json](source_manifest.json). Equations are manually
transcribed into [audit_checks.py](audit_checks.py); the code is not a TeX parser.
The standalone `unified-biquaternion-theory` repository is outside this audit.

From the repository root, with Python 3.12:

```sh
python -m venv .venv-scalar-g
.venv-scalar-g/bin/python -m pip install -r audits/scalar_g/requirements.txt
.venv-scalar-g/bin/python -B audits/scalar_g/audit_checks.py -v
.venv-scalar-g/bin/python -B -m unittest discover -s audits/scalar_g -p '*checks.py' -v
```

The original suite contains 18 exact symbolic checks, including an independent 2x2 matrix
representation, differentiation of arbitrary smooth potentials, an explicit
spatially decaying pure gauge, Euler-Lagrange equations, and a Legendre transform.
It verifies the stated identities and counterexamples, not experimental physics
or a proof-assistant formalization of the whole theory. A passing suite records
the counterexamples as well as the identities that survive.

## 1. Conventions and the identity that survives

The basis is the one explicitly defined in
[pauli12.wxm](../../FTL-problem/pauli12.wxm):

$$
I_q^2=J_q^2=K_q^2=-1,\qquad I_qJ_q=K_q,
$$

with cyclic products and a commuting complex unit $i$. A pure quaternion vector
satisfies $\mathbf v\mathbf w=-\mathbf v\cdot\mathbf w+\mathbf v\times\mathbf w$.
For $Q=a+\mathbf v$, quaternion conjugation is $Q^+=a-\mathbf v$;
complex conjugation acts on coefficients. Write $Q^\dagger=(Q^+)^*$.
In the supplied matrix representation this is the Hermitian adjoint.

Use real electromagnetic fields, $c>0$, $\mu>0$, and $A_0=\phi/c$.
The original potential and derivative give

$$
X=\widehat\Box\widehat A=G-\mathbf B-i\mathbf E/c,
\qquad G=c^{-2}\partial_t\phi+\nabla\cdot\mathbf A.
$$

The component expansion in
[biquaternion-gradient-of-vector-potential.tex](../../theory-of-everything/latex/biquaternion-gradient-of-vector-potential.tex)
is correct with these conventions. Test 03 checks every independent first
derivative coefficient. This is an algebraic identity, not yet a field equation.

## 2. Exact energy discrepancy

The definition in
[energy-simple-calculation.tex](../../theory-of-everything/latex/energy-simple-calculation.tex)
is $\widehat W=-XX^\dagger/(2\mu)$, with
$X^\dagger=G^*+\mathbf B-i\mathbf E/c$.
Multiplying gives

$$
\mu\widehat W=
-\frac{|G|^2+|\mathbf B|^2+|\mathbf E|^2/c^2}{2}
+\frac{i}{c}\operatorname{Re}(G)\mathbf E
-i\operatorname{Im}(G)\mathbf B
-\frac{i}{c}\mathbf B\times\mathbf E.
$$

The vector terms agree with the historical expansion. The electric and magnetic
scalar terms have the opposite sign to
[energy-complex-G.tex](../../theory-of-everything/latex/energy-complex-G.tex)
and [energy-real-G.tex](../../theory-of-everything/latex/energy-real-G.tex).
For $G=E=0$ and a unit magnetic field, the definition yields $-1/(2\mu)$
and the published expansion yields $+1/(2\mu)$.

Changing only the overall sign makes **all three squared scalar terms positive**;
it cannot produce negative $|G|^2$ together with positive electromagnetic energy.
Thus an overall-sign correction does not derive the proposed scalar energy.

A consistent reference for the Maxwell sector is to remove the scalar component,
$P=X-\operatorname{Sc}X=-\mathbf B-i\mathbf E/c$, and use

$$
u_{\rm EM}=\frac{\operatorname{Sc}(PP^\dagger)}{2\mu}
=\frac{|\mathbf B|^2+|\mathbf E|^2/c^2}{2\mu},
\qquad \mathbf S=\frac{\mathbf E\times\mathbf B}{\mu}.
$$

With this particular encoding $PP^\dagger/(2\mu)=u_{\rm EM}-i\mathbf S/c$.
This packages the density and energy flux in the chosen frame. It does not make
the package a Lorentz four-vector or identify it with the full stress tensor.
The action-derived Maxwell stress tensor, for signature $(+---)$, is

$$
T^{\mu\nu}=-F^{\mu\rho}F^\nu{}_{\rho}
+\tfrac14\eta^{\mu\nu}F_{\alpha\beta}F^{\alpha\beta}.
$$

Its $T^{00}$ is the positive density above, in the appropriate units. Tests 08-09
check both constructions. The scalar projection is a Maxwell reference, not a new
physical prescription for retaining a measurable G.

## 3. Gauge test and a finite counterexample

For the standard electromagnetic gauge transformation

$$
\mathbf A'=\mathbf A+\nabla\chi,\qquad
\phi'=\phi-\partial_t\chi,\qquad
\Box=c^{-2}\partial_t^2-\nabla^2,
$$

one obtains

$$
\mathbf E'=\mathbf E,\quad \mathbf B'=\mathbf B,\quad
G'=G-\Box\chi.
$$

This is checked for arbitrary smooth potentials and gauge function in test 10.
In Maxwell theory the choice of G is therefore not a new local observable.
An electromagnetic gauge transformation is not a change of spacetime coordinates
or a derivation of gravitational acceleration.

This is not an objection that relies on divergent fields at spatial infinity.
Start with zero potential on all of $\mathbb R^3$ and choose the time-independent,
smooth, globally single-valued function

$$
\chi=a e^{-r^2/L^2},\quad L>0.
$$

Then $\phi'=0$, $\mathbf A'=\nabla\chi$, and $E'=B'=0$, while

$$
G'=a\left(\frac{4r^2}{L^4}-\frac{6}{L^2}\right)e^{-r^2/L^2},
\qquad
\int_{\mathbb R^3}|G'|^2\,d^3x
=\frac{15\pi^{3/2}a^2}{2\sqrt2 L}.
$$

The purported scalar energy would be
$-15\pi^{3/2}a^2/(4\sqrt2\mu L)$ for a potential gauge equivalent to zero.
The gauge function and its derivatives decay at infinity, so no boundary charge
or nontrivial Aharonov-Bohm holonomy is involved. Test 11 checks the Laplacian
and the integral exactly. If a new theory makes this transformation physical,
it must supply the action, physical state space, and coupling that justify it;
Maxwell gauge redundancy can no longer be assumed unchanged.

## 4. An attempted dynamical completion, with explicit limits

The old equations do not supply an action deriving the scalar energy. Rather than
assuming one is healthy, examine the simplest relevant class. **This is a
diagnostic ansatz, not a consequence already derived from UBT.**

Assumptions for this section only:

- One real vector potential on flat four-dimensional Minkowski spacetime.
- Local, Lorentz-invariant, parity-even, quadratic first-derivative terms with
  constant coefficients; no mass, other fields, background tensors, or new
  constraints. Smooth fields and boundary conditions permit integration by parts.
- Positive normalization of the ordinary transverse Maxwell sector.

In units $c=\mu=1$, define $A^\mu=(\phi,\mathbf A)$,
$A_\mu=(\phi,-\mathbf A)$, $G=\partial_\mu A^\mu$, and
$F_{\mu\nu}=\partial_\mu A_\nu-\partial_\nu A_\mu$.
The first-derivative contractions reduce, up to a boundary term, to

$$
\mathcal L_\lambda=-\tfrac14 F_{\mu\nu}F^{\mu\nu}
+\tfrac\lambda2 G^2-J^\mu A_\mu.
$$

For completeness, let $I_1=\partial_\mu A_\nu\partial^\mu A^\nu$ and
$I_2=\partial_\mu A_\nu\partial^\nu A^\mu$. Then

$$
F^2=2(I_1-I_2),\qquad
I_2-G^2=\partial_\mu
\left(A_\nu\partial^\nu A^\mu-A^\mu G\right).
$$

The three parity-even index contractions are $I_1,I_2,G^2$, so these identities
leave the two displayed bulk terms. Test 12 verifies the identities; the invariant
classification uses the stated Lorentz and field-content assumptions. No argument
here fixes a nonzero value of $\lambda$ from the historical premises.

Varying the action yields

$$
\partial_\mu F^{\mu\nu}-\lambda\partial^\nu G=J^\nu,
\qquad -\lambda\Box G=\partial_\nu J^\nu.
$$

For a conserved current and $\lambda\ne0$, $\Box G=0$.
**This does not force G to vanish**: homogeneous initial data remain possible.
It also does not prove that these data are healthy physical states.
Tests 13-14 derive the equations and their divergence independently from the action.

## 5. Hamiltonian: both nonzero signs fail on the unrestricted phase space

Take the four covariant components $q_\nu=A_\nu$ as canonical coordinates and
write spatial repeated indices as Euclidean sums. For zero external current:

$$
\pi_0=\lambda(\dot A_0-\partial_i A_i)=\lambda G,
\qquad \pi_i=\dot A_i-\partial_i A_0.
$$

For $\lambda\ne0$ the velocity Hessian is
$\operatorname{diag}(\lambda,1,1,1)$ and is nonsingular. Thus no primary
constraint arises from this Lagrangian to remove the extra canonical directions.
The exact Legendre transform gives

$$
\mathcal H_\lambda=
\tfrac12\sum_i\pi_i^2+\tfrac14\sum_{i,j}F_{ij}^2
+\sum_i\pi_i\partial_i A_0+\pi_0\partial_i A_i
+\frac{\pi_0^2}{2\lambda}.
$$

Tests 15-16 verify the Hessian, momenta, and Legendre transform with symbolic
nonzero $\lambda$.

**If $\lambda<0$:** choose initially $A_\mu=0$, $\pi_i=0$ and a nonzero smooth
localized $\pi_0$. The Hamiltonian is $\int\pi_0^2/(2\lambda)\,d^3x<0$ and
tends to $-\infty$ as the amplitude is increased. This is a negative kinetic direction.

**If $\lambda>0$:** choose initially

$$
A_0=f(\mathbf x),\quad A_i=0,\quad
\pi_i=-\partial_i f,\quad\pi_0=0,
$$

where $f$ is smooth, nonconstant, and spatially localized. Then

$$
H_\lambda=-\tfrac12\int|\nabla f|^2\,d^3x<0.
$$

Scaling $f$ gives another family tending to $-\infty$. These are allowed initial
data for the unrestricted nondegenerate action. They need not be stationary
solutions. An instantaneous G of zero does not exclude them. Tests 17-18 verify
both families. The conclusion is unbounded canonical energy in this ansatz, not
a claim that every solution grows exponentially.

**If $\lambda=0$:** the Legendre transform above is inapplicable. Instead
$\pi_0=0$ is a primary constraint and Gauss' law is a secondary constraint.
After reduction the Maxwell field energy is positive and there are two photon
polarizations. Thus the preceding negative directions cannot be imported into
the Maxwell physical phase space.

One may use a $G^2$ term as gauge fixing with appropriate physical-state
conditions, as in standard covariant quantization. In that interpretation it is
not an independently observable scalar energy. Classically, for conserved
sources, imposing G and its time derivative to vanish initially preserves the
Maxwell sector. This is not the same as retaining unrestricted physical G modes.

This obstruction is restricted to the listed ansatz. It does **not** exclude an
independent healthy scalar, additional constraints, a different field content,
or a principle-derived completion in another theory. None of those completions
has been derived or validated by this audit.

## 6. Consequence for the research track

| Claim | Outcome |
|---|---|
| The stated potential-gradient expansion is algebraically valid | Retain |
| The stated product derives the mixed-sign scalar energy | Rejected by exact multiplication |
| G is a new local Maxwell observable | Rejected by a smooth, decaying pure gauge |
| A physical quadratic G term automatically supplies healthy dynamics | Rejected in the explicit unrestricted single-vector ansatz |
| Standard gauge fixing supplies a new physical scalar energy | Does not follow; physical-state conditions are essential |
| Scalar gravity, dark matter, teleportation, or FTL follow from these formulas | Not established |
| The entire present UBT is disproved | Not assessed and does not follow |

The historical standalone scalar-energy mechanism should not be used as a
validated foundation for device specifications or a UBT prediction. Keep the
verified Maxwell algebra. Reopening the physical scalar track requires a
principle-derived action and constraints with an acceptable physical energy,
followed by a gauge-independent observable distinct from Maxwell theory.
An assumption chosen merely to remove one counterexample is not such a derivation.

## Sources and attribution

- The eight historical source files and their exact digests are listed in
  [source_manifest.json](source_manifest.json); these fix the audited conventions.
- David Tong, [Quantum Field Theory, chapter 6](https://www.damtp.cam.ac.uk/user/tong/qft/qfthtml/S6.html),
  sections 6.1.1, 6.2.1, 6.2.2: gauge redundancy, Maxwell constraints, covariant
  gauge fixing, and the physical-state condition. These are standard reference
  facts; the exact energy multiplication and the two Hamiltonian counterexamples
  are derived explicitly above.
- [SymPy matrix documentation](https://docs.sympy.org/latest/modules/matrices/matrices.html):
  computational reference. The requirements pin SymPy 1.14.0 and mpmath 1.3.0.
