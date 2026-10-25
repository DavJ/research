# Full Gauss constraint, boundary charge, and the commuting-Dirac energy gate

<!-- BILINGUAL-UNIT: full-gauss.scope -->

## 1. Scope and independent variables

Date: 2026-10-25. This follows the [charge/coframe audit](ubt_dirac_charge_gate.en.md) and the now-merged [UBT integration #730](https://github.com/UBT-Institute/unified-biquaternion-theory/pull/730). It supplies a conditional comparison, not a fundamental UBT Hamiltonian. Immutable sources are in [full_gauss_sources.json](full_gauss_sources.json).

Assume smooth commuting amplitudes on a prescribed flat spatial hypersurface, the chosen real-linear map F, and its constant pulled-back Dirac form. For this comparator only, an independent canonical vector-potential/flux pair is available. Those variables are not derived from Theta and are not added to canonical UBT. Their role is to test what a complete Gauss constraint would change. The composite UBT tetrad/connection, its induced symplectic terms and the real-coframe transformation still require derivation. In particular the Gaussian data below are not asserted to generate a nondegenerate canonical UBT geometry.

Here x denotes the real component vector; y denotes spatial position. A fixed positive spatial measure is used. The positive matter moment density has zero additive constant:

\[
x\in\mathbb R^8,\quad u=F(\Theta),\quad
\Omega_D=\operatorname{diag}(J_2,J_2,-J_2,-J_2),\quad
J_2=\begin{pmatrix}0&-1\\1&0\end{pmatrix},\quad
\rho=\frac12x^Tx=\frac12u^\dagger u.
\]

<!-- BILINGUAL-UNIT: full-gauss.generator -->

## 2. Derive the bulk generator and its boundary term

Choose the following Hamiltonian sign convention explicitly. It differs from the moment-map sign convention in the preceding audit only in the definition of the Hamiltonian generator. Reverse the phase parameter so that the ordinary spinor phase is negative. With the canonical flux momentum held invariant, contraction with the full comparator symplectic form gives the displayed result by integration by parts. The parameter is fixed under phase-space variation.

For parameters vanishing on the boundary, the local constraint is the charge density minus the flux divergence, rather than the matter density alone. Its Abelian brackets vanish: the matter norm is phase invariant, flux momenta commute, and the constraint contains no vector potential. On a finite region a nonvanishing boundary parameter requires the surface improvement shown. On the constraint surface a constant asymptotic parameter therefore measures the total charge; it cannot automatically be discarded as a zero-charge gauge redundancy.

\[
\omega_\Sigma=\int_\Sigma\left[\frac12(\Omega_D)_{AB}\,\delta x^A\wedge\delta x^B
+\delta\Pi^i\wedge\delta A_i\right]d^3y,\qquad
\iota_{X_H}\omega_\Sigma=-\delta H.
\]
\[
K_\alpha x=-\alpha\Omega_Dx,\quad K_\alpha A_i=\partial_i\alpha,\quad K_\alpha\Pi^i=0,
\qquad u'=e^{-i\alpha}u,\quad A'_i=A_i+\partial_i\alpha.
\]
\[
\boxed{\iota_{K_\alpha}\omega_\Sigma
=-\delta\int_\Sigma\alpha\bigl(\rho-\partial_i\Pi^i\bigr)d^3y
-\int_{\partial\Sigma}\alpha\,\delta\Pi^i n_i\,dS.}
\]
\[
\mathcal C=\rho-\partial_i\Pi^i=0,\quad
G_\alpha=\int_\Sigma\alpha\mathcal C\,d^3y
+\int_{\partial\Sigma}\alpha\Pi^in_i\,dS,\quad
\{\mathcal C(y),\mathcal C(z)\}=0.
\]

<!-- BILINGUAL-UNIT: full-gauss.boundary -->

## 3. The global restriction depends on the boundary

Integrate the constraint. On a compact hypersurface without boundary, or in a zero-total-flux sector, positivity forces the commuting amplitudes to vanish. This conclusion uses the stated classical moment density and the absence of other charge contributions or a shifted level. It is not a theorem about Grassmann fields or a normal-ordered fermionic charge operator.

On noncompact space, pointwise decay of the flux momentum is insufficient to force zero integrated flux. A Coulomb tail decays and still carries nonzero surface charge. Thus the preceding zero-level matter-only obstruction cannot be applied by merely saying that fields decay at infinity.

\[
Q:=\int_\Sigma\rho\,d^3y
=\int_{\partial\Sigma}\Pi^in_i\,dS.
\]
\[
Q=0,\quad\rho=\frac12\sum_{A=1}^8(x^A)^2\ge0
\quad\Longrightarrow\quad x=0
\qquad x\in C^\infty(\Sigma,\mathbb R^8).
\]
\[
\Pi^i=O(r^{-2})\longrightarrow0
\quad\not\Longrightarrow\quad
\lim_{r\to\infty}\int_{S_r}\Pi^in_i\,dS=0.
\]

<!-- BILINGUAL-UNIT: full-gauss.gaussian -->

## 4. A smooth nonzero solution of the comparator Gauss constraint

For positive charge and width choose the radial Gaussian density below. Its flux is smooth at the origin, solves Gauss everywhere by smooth extension, and decays at large radius while carrying the prescribed charge. The potential is used only to compute the flux and its positive energy.

The electrostatic energy follows either from the charge-potential integral or from the Gaussian Fourier transform. An independent numerical channel integrates the squared radial flux and its Coulomb tail. This establishes nontrivial finite-energy constraint data in the comparator. It does not establish a self-consistent UBT coframe or a selected Maxwell sector.

\[
\rho_L(r)=\frac{Q}{\pi^{3/2}L^3}e^{-r^2/L^2},\qquad Q>0,\ L>0,\quad s=r/L,
\]
\[
V_L(r)=\frac{Q}{4\pi r}\operatorname{erf}(s),\qquad
\boldsymbol\Pi_L=-\nabla V_L
=\frac{Q}{4\pi r^2}\left[\operatorname{erf}(s)-\frac{2s}{\sqrt\pi}e^{-s^2}\right]\widehat{\mathbf r}.
\]
\[
\nabla\cdot\boldsymbol\Pi_L=\rho_L,\qquad
\boldsymbol\Pi_L=\frac{Q}{3\pi^{3/2}L^3}\mathbf y+O(r^3),\qquad
\lim_{r\to\infty}4\pi r^2\Pi_{L,r}=Q.
\]
\[
\boxed{U_L=\frac12\int_{\mathbb R^3}|\boldsymbol\Pi_L|^2d^3y
=\frac12\int_{\mathbb R^3}\rho_LV_Ld^3y
=\frac{Q^2}{4\sqrt2\,\pi^{3/2}L}>0.}
\]

<!-- BILINGUAL-UNIT: full-gauss.hamiltonian -->

## 5. Specify a gauge-compatible Hamiltonian for the comparison

Now specify, rather than derive from UBT, the ordinary flat Maxwell/commuting-Dirac comparator Hamiltonian. The chosen symplectic normalization fixes the matter prefactor. The temporal potential is a multiplier with vanishing conjugate momentum. Covariant momentum transforms with the spinor phase, so the Hamiltonian is gauge invariant. The continuity equation and the flux equation preserve the Gauss constraint: it is not merely a one-time algebraic cancellation.

The positive spinor norm does not imply positive energy. The free Dirac symbol has both energy branches. The following initial-data family survives Gauss reduction and the Coulomb gauge condition; it need not be stationary under the interacting evolution.

\[
h_D(\mathbf p)=\begin{pmatrix}-\boldsymbol\sigma\cdot\mathbf p&mI_2\\mI_2&\boldsymbol\sigma\cdot\mathbf p\end{pmatrix},
\quad\boldsymbol\alpha_D=\operatorname{diag}(-\boldsymbol\sigma,+\boldsymbol\sigma),\quad m>0,
\]
\[
H_0=\frac12\int u^\dagger h_D(-i\nabla+\mathbf A)u\,d^3y
+\frac12\int\bigl(|\boldsymbol\Pi|^2+|\nabla\times\mathbf A|^2\bigr)d^3y,
\qquad H_{\rm tot}=H_0+\int A_0\mathcal C\,d^3y.
\]
\[
(-i\nabla+\mathbf A')u'=e^{-i\alpha}(-i\nabla+\mathbf A)u,\quad
\mathbf j=\frac12u^\dagger\boldsymbol\alpha_Du,\quad
\dot\rho=-\nabla\cdot\mathbf j,\quad
\dot{\boldsymbol\Pi}=-\nabla\times(\nabla\times\mathbf A)-\mathbf j,
\quad\dot{\mathcal C}=0.
\]

<!-- BILINGUAL-UNIT: full-gauss.energy -->

## 6. Exact unbounded energy at fixed nonzero charge

Choose the normalized negative-energy eigenvector shown for momentum along the spatial axis. Multiply it by a real Gaussian envelope and a plane phase. The charge density is the same Gaussian for every momentum; therefore the same flux solves Gauss for the entire family. The potential can enforce Coulomb gauge in time, but its constraint multiplier vanishes from the energy on the constraint surface.

The envelope derivative contributes a vanishing integrated total derivative. The matter energy therefore equals the negative Dirac branch times the fixed charge, while the electrostatic energy is independent of momentum. Increasing momentum makes the total energy arbitrarily negative at fixed charge and fixed width. Each datum is smooth and has finite energy. This is a lower-bound counterexample on the comparator constraint surface, not a claim that every solution grows exponentially.

Both a positive norm and a complete Abelian Gauss constraint are thus insufficient for healthy commuting Dirac matter in this benchmark. Reversing an overall energy convention cannot remove both spectral signs. This is the familiar need to distinguish a classical commuting spinor from a fermionic quantum field, now exhibited with the charge constraint retained. It does not rule out a separately derived UBT quantum statistics, different constraints, a physical sector reduction or different dynamics. A positive-frequency restriction would itself require justification and preservation by local interactions; it is not supplied here.

\[
E_k=\sqrt{k^2+m^2},\quad
v_-(k)=\frac{(m,0,k-E_k,0)^T}{\sqrt{m^2+(k-E_k)^2}},\quad
h_D(k\widehat{\mathbf z})v_-=-E_kv_-,\quad v_-^\dagger v_-=1.
\]
\[
u_k(\mathbf y)=\sqrt{2\rho_L(r)}\,e^{ikz}v_-(k),\quad
\mathbf A=0,\quad\boldsymbol\Pi=\boldsymbol\Pi_L,\quad
\mathcal C=0,\quad \nabla\cdot\mathbf A=0.
\]
\[
\int f_L\partial_i f_L\,d^3y=0,\qquad f_L=\sqrt{2\rho_L},\qquad
\boxed{H_0[u_k,0,\Pi_L]=-Q\sqrt{k^2+m^2}+\frac{Q^2}{4\sqrt2\,\pi^{3/2}L}
\xrightarrow[k\to\infty]{}-\infty.}
\]

<!-- BILINGUAL-UNIT: full-gauss.decision -->

## 7. What this narrows in the UBT programme

The constructive result is a complete conditional bulk/boundary Gauss generator and explicit nonzero finite-flux data. The obstruction is equally concrete: that constraint does not repair the unrestricted commuting Dirac energy. These are statements about the specified comparator, whose independent canonical flux has not been obtained from the single Theta architecture.

For canonical UBT the next necessary object is the full presymplectic current and local generator after substituting the selected composite tetrad and connection, including their variations. It must specify the boundary sector, the physical statistics or positive-energy reduction, and how the candidate phase acts on the real coframe. Until those objects are derived, neither the Dirac norm nor the flux benchmark selects the fundamental Hamiltonian. No new potential or observable follows from this note.

<!-- BILINGUAL-UNIT: full-gauss.verification -->

## 8. Verification and sources

[full_gauss_checks.py](full_gauss_checks.py) has 19 focused tests. Exact SymPy 1.14.0 checks cover generator signs, integration by parts including the surface term, gauge covariance, Gaussian normalization/divergence/origin/flux, two energy evaluations and the negative Dirac branch. Independent Python 3.12 channels use 50 direct-complex eigenvector samples and Simpson quadrature with 4096 intervals plus the Coulomb tail; the energy tolerance is 1e-10. The tests encode the stated conditional identities, not a derivation of UBT dynamics. LEAN-PENDING: Lean and Lake are absent in this runtime; no compiled formal proof is supplied.

The full audit now has 51 tests. English is the translation source; paired equations, code, numbers, structure and caveats are synchronized. Machine signatures do not attest human semantic review. The repository merge snapshot, including the older unmerged PRs and their concrete blockers, is in [merge_state_2026-10-25.json](merge_state_2026-10-25.json).

Background references are David Tong’s [QFT chapter on Maxwell constraints and gauge symmetry](https://www.damtp.cam.ac.uk/user/tong/qft/qfthtml/S6.html) and [chapter on Dirac quantization and statistics](https://www.damtp.cam.ac.uk/user/tong/qft/qfthtml/S5.html). The explicit conventions, Gaussian datum and fixed-charge energy calculation above are derived here. This standard Dirac-statistics issue is not claimed as a new physical discovery.

```sh
python -B -m unittest discover -s audits/scalar_g -p '*checks.py' -v
```
