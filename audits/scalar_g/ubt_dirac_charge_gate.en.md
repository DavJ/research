# UBT continuation: Dirac charge, the real coframe, and the gauge constraint

## 1. Scope and source boundary

Date: 2026-10-24. Working mathematical comparison; no fundamental action,
physical gauge group, mass, or charge normalization is selected here.

The [historical scalar audit](README.md) does not transfer automatically to
canonical UBT. This continuation tests a particular newer candidate: the
real-linear map in merged UBT #724 and the chosen symplectic pullback in draft
UBT #726. The latter was an **unmerged draft at the inspected revision**. Sources
and immutable revisions are in [ubt_reference_sources.json](ubt_reference_sources.json).
The [Czech edition](ubt_dirac_charge_gate.cs.md) has the same scope and derivation.

Assume commuting real coordinates for one complex 2x2 Theta matrix, a chosen
right-column frame, and the specified flat Dirac generator. Separately test the
algebraic canonical coframe readout. This does not establish that the uniform-left
spinor transformation and the canonical coframe representation are already
compatible. It does not identify the old electromagnetic scalar G with a new
Theta observable. The pointwise positive norm used below is not a proof that a
Dirac Hamiltonian has a lower bound.

## 2. The two phase actions

Write the chosen map and its inverse information as

$$
\Theta=[\psi,\chi],\qquad
\epsilon=\begin{pmatrix}0&1\\-1&0\end{pmatrix},\qquad
F(\Theta)=u=\begin{pmatrix}\psi\\\epsilon\chi^*\end{pmatrix}.
$$

F is a real-linear bijection, not a complex-linear one. For real phi, a central
phase on Theta induces opposite phases on the Weyl components:

$$
F(e^{i\phi}\Theta)=e^{i\phi Q_A}u,
\qquad Q_A=\operatorname{diag}(I_2,-I_2).
$$

The ordinary vector phase of a Dirac spinor instead pulls back to

$$
F(\Theta R_\phi)=e^{i\phi}u,\qquad
R_\phi=\operatorname{diag}(e^{i\phi},e^{-i\phi})\in SU(2).
$$

The pullback is unique once F and its right frame are chosen, since F is
bijective. The choice of right axis itself is not intrinsic: a right SU(2)
frame change can conjugate sigma_3 into sigma_1. Thus these formulas identify
the candidate's vector phase, not an independently derived electromagnetic U(1).

## 3. Mass and moment maps distinguish them

For the pinned candidate use real momentum and mass, with

$$
h_D(p)=\begin{pmatrix}-\boldsymbol\sigma\cdot\mathbf p&mI_2\\
mI_2&\boldsymbol\sigma\cdot\mathbf p\end{pmatrix},\qquad
\dot u=-ih_Du.
$$

Direct multiplication gives

$$
[h_D,Q_A]=\begin{pmatrix}0&-2mI_2\\2mI_2&0\end{pmatrix},
\qquad [h_D,I_4]=0.
$$

Consequently the central Theta phase is not a symmetry of this fixed massive
Dirac generator. In particular, for the unnormalized vector u=(1,0,i,0),

$$
\frac{d}{dt}(u^\dagger Q_Au)=4m.
$$

For m=0 the axial phase is conserved in this classical free calculation, but
the opposite charge weights remain different from the vector phase. A charged
order parameter or another mass-generation mechanism would need its own
derivation; none is inserted here.

Order the eight real coordinates as Re/Im of psi_1, psi_2, chi_1, chi_2.
Let J_2=((0,-1),(1,0)), J_8=diag(J_2,J_2,J_2,J_2), and let Q be the real
Jacobian of F. The selected pullback is

$$
\Omega_D=Q^TJ_8Q=\operatorname{diag}(J_2,J_2,-J_2,-J_2).
$$

Use the convention iota_(Kx) Omega_D=d mu, with mu(0)=0. Then
Hessian(mu)=-Omega_D K. The central and vector-phase generators give

$$
\mu_C=\tfrac12(\|\psi\|^2-\|\chi\|^2),\qquad
\mu_Q=\tfrac12(\|\psi\|^2+\|\chi\|^2).
$$

Both phase actions preserve Omega_D; preservation of the symplectic form does
not imply that both preserve the chosen Hamiltonian. Neither moment map equals
the historical divergence G.

## 4. Metric preservation does not imply preservation of the real coframe

On the canonical Lorentz slice, in a Pauli basis,

$$
E_\mu=i e_\mu^0I_2-i e_\mu^k\sigma_k,\qquad E_\mu^\dagger=-E_\mu,
\qquad
\tfrac12(E_\mu^\sharp E_\nu+E_\nu^\sharp E_\mu)=g_{\mu\nu}I_2.
$$

Here sharp is the complex-linear quaternion conjugation, represented by the
2x2 adjugate, not the Hermitian adjoint. Under the **hypothesized right-covariant
law** E'_mu=E_mu R, algebra gives

$$
\tfrac12[(E_\mu R)^\sharp(E_\nu R)+(E_\nu R)^\sharp(E_\mu R)]
=(\det R)g_{\mu\nu}I_2.
$$

Therefore R_phi preserves the full central metric identity. For the real
timelike basis element E_0=iI_2, however,

$$
E_0R_\phi+(E_0R_\phi)^\dagger
=\operatorname{diag}(-2\sin\phi,2\sin\phi).
$$

The transformed coframe is generally outside the fixed anti-Hermitian slice
even though its metric is unchanged. More generally, preserving that slice for
every vector in a nondegenerate coframe requires R=+I_2 or R=-I_2 when det R=1.
Proof: use E=iI_2 to obtain R^dagger=R; the three spatial basis elements then
force R to commute with every Pauli matrix. Thus R=rI_2 with real r, and det R=1
forces r^2=1. The checker independently solves the real linear conditions:
rank seven in eight real entries, followed by the determinant condition.

This is an obstruction to the **simple slice-preserving right action**, not
to every electromagnetic realization in UBT. A derived gauge-orbit completion
could allow real representatives to move outside the chosen slice while keeping
the metric physical. A derived compensating transformation could also change
the conclusion. Its connection law, constraints, and physical readout have not
been supplied by the chosen F. The canonical architecture is not changed here.

## 5. A local gauge redundancy needs more than a positive matter moment map

On a prescribed real-time hypersurface with fixed positive density, the
ultralocal candidate matter symplectic form is the integral of Omega_D. If
the vector phase is made a local redundancy **solely by imposing the zero-level
matter moment-map constraint**, with no electric-flux momentum, derivative
contribution, background charge, or nonzero level, then

$$
\mu_Q(x)=0\quad\Longrightarrow\quad
\sum_{A=1}^{8}(x^A(x))^2=0\quad\Longrightarrow\quad\Theta(x)=0.
$$

For smooth fields and finite linear covariant connections this makes DTheta=0
and the composite coframe degenerate. Thus this specific minimal auxiliary
gauging cannot describe nonzero commuting Theta amplitudes.

The hypotheses matter. A genuine Gauss constraint may instead contain an
electric-flux divergence that balances the matter charge. A selected composite
connection could change the full symplectic structure through its induced
variations. A nonzero moment-map level could avoid the zero solution, but its
value and physical meaning would be additional data requiring derivation.
None is assumed here. This argument concerns ordinary commuting real
coordinates, **not** Grassmann-valued fermionic phase space or a normal-ordered
quantum charge operator. Derivation of fermionic statistics is a separate gate.

## 6. Verification and the next decision

[dirac_charge_checks.py](dirac_charge_checks.py) supplies 14 checks: exact
SymPy phase identities, the mass commutator, the two moment maps, the general
right-factor metric identity, the slice-preserving subgroup, and 50 independent
Python-complex samples of phases and charge evolution. The numerical channel
does not use SymPy matrix formulas; sampling is not a proof of the analytic
statements. Formal status is LEAN-PENDING: Lean and Lake are unavailable in the
inspected runtime, and no compiled Lean proof is supplied.

Run all 32 scalar and continuation checks from the repository root:

```sh
python -B -m unittest discover -s audits/scalar_g -p '*checks.py' -v
```

The next constructive requirement is a **derived local constraint generator**
for this candidate vector phase, with its full symplectic form and induced
coframe/connection transformation. It must permit nonzero physical Theta data,
preserve the physical metric, and explain the role of the real slice. That is
a sharper target than adding a new potential or relabeling the old G.
The fundamental Hamiltonian, microscopic action, and new observable remain open.

## 7. References

- Immutable UBT sources, including merged #724 and the inspected draft #726:
  [source record](ubt_reference_sources.json).
- David Tong, [Quantum Field Theory, chapter 4](https://www.damtp.cam.ac.uk/user/tong/qft/qfthtml/S4.html):
  standard Dirac/Weyl representations and currents. The displayed pullbacks and
  commutator are calculated explicitly here.
- Ana Cannas da Silva, [Lectures on Symplectic Geometry](https://people.math.ethz.ch/~acannas/Papers/lsg.pdf),
  Hamiltonian actions and reduction: moment maps depend on conventions and may
  be shifted by constants. The normalization and zero-level assumptions above
  are explicit.
