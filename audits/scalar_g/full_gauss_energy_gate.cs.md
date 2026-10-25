# Úplná Gaussova vazba, okrajový náboj a energetická podmínka komutujícího Diracova pole

<!-- BILINGUAL-UNIT: full-gauss.scope -->

## 1. Rozsah a nezávislé proměnné

Datum: 2026-10-25. Navazuje na [audit náboje a kofrámce](ubt_dirac_charge_gate.cs.md) a nyní sloučenou [integraci UBT #730](https://github.com/UBT-Institute/unified-biquaternion-theory/pull/730). Jde o podmíněné srovnání, nikoli fundamentální Hamiltonián UBT. Neměnné zdroje jsou v [full_gauss_sources.json](full_gauss_sources.json).

Předpokládáme hladké komutující amplitudy na předepsané ploché prostorové nadploše, zvolené reálně lineární zobrazení F a jeho konstantní zpětně přenesenou Diracovu formu. Pouze pro tento srovnávací model je dostupná nezávislá kanonická dvojice vektorového potenciálu a toku. Tyto proměnné nejsou odvozeny z Theta ani přidány do kanonické UBT. Slouží ke zkoušce, co by změnila úplná Gaussova vazba. Kompozitní tetráda a konexe UBT, její indukované symplektické členy a transformace reálného kofrámce stále vyžadují odvození. Níže uvedená gaussovská data zejména nejsou vydávána za generátor nedegenerované kanonické geometrie UBT.

Zde x označuje vektor reálných složek a y prostorovou polohu. Používáme pevnou kladnou prostorovou míru. Kladná hustota materiálové momentové mapy má nulovou aditivní konstantu:

\[
x\in\mathbb R^8,\quad u=F(\Theta),\quad
\Omega_D=\operatorname{diag}(J_2,J_2,-J_2,-J_2),\quad
J_2=\begin{pmatrix}0&-1\\1&0\end{pmatrix},\quad
\rho=\frac12x^Tx=\frac12u^\dagger u.
\]

<!-- BILINGUAL-UNIT: full-gauss.generator -->

## 2. Odvození objemového generátoru a okrajového členu

Výslovně zvolíme následující znaménkovou konvenci Hamiltonova generátoru. Od konvence momentové mapy v předchozím auditu se liší pouze definicí Hamiltonova generátoru. Obrátíme parametr fáze, takže běžná spinorová fáze je záporná. Při invariantní kanonické hybnosti toku dává kontrakce s úplnou srovnávací symplektickou formou uvedený výsledek pomocí integrace per partes. Parametr se při variaci fázového prostoru nemění.

Pro parametry mizející na hranici je lokální vazbou hustota náboje minus divergence toku, nikoli samotná materiálová hustota. Její abelovské závorky mizí: materiálová norma je fázově invariantní, hybnosti toku komutují a vazba neobsahuje vektorový potenciál. Na konečné oblasti vyžaduje nenulový okrajový parametr uvedené povrchové doplnění. Konstantní asymptotický parametr tedy na ploše vazeb měří celkový náboj; nelze jej automaticky zahodit jako gauge redundanci s nulovým nábojem.

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

## 3. Globální omezení závisí na hranici

Integrujeme vazbu. Na kompaktní nadploše bez hranice nebo v sektoru s nulovým celkovým tokem vynucuje kladnost nulové komutující amplitudy. Tento závěr používá uvedenou klasickou momentovou hustotu a nepřítomnost dalších nábojových příspěvků či posunuté hladiny. Nejde o větu pro Grassmannova pole nebo normálně uspořádaný fermionový operátor náboje.

Na nekompaktním prostoru nestačí bodový pokles hybnosti toku k vynucení nulového integrovaného toku. Coulombovský chvost klesá a přesto nese nenulový povrchový náboj. Předchozí překážku nulové hladiny samotné materiálové momentové mapy tedy nelze použít pouhým tvrzením, že pole v nekonečnu klesají.

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

## 4. Hladké nenulové řešení srovnávací Gaussovy vazby

Pro kladný náboj a šířku zvolíme níže uvedenou radiální gaussovskou hustotu. Její tok je v počátku hladký, po hladkém rozšíření splňuje Gaussovu rovnici všude a pro velký poloměr klesá, přičemž nese předepsaný náboj. Potenciál slouží pouze k výpočtu toku a jeho kladné energie.

Elektrostatická energie plyne buď z integrálu hustoty náboje s potenciálem, nebo z Fourierovy transformace gaussovské hustoty. Nezávislý numerický postup integruje kvadrát radiálního toku a jeho Coulombův chvost. Tím jsou ve srovnávacím modelu doložena netriviální data vazby s konečnou energií. Samokonzistentní kofrámec UBT ani vybraný Maxwellův sektor tím doložen není.

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

## 5. Určení gauge kompatibilního Hamiltoniánu pro srovnání

Nyní určíme, místo abychom jej vydávali za odvozený z UBT, obvyklý plochý srovnávací Hamiltonián Maxwellova a komutujícího Diracova pole. Zvolená symplektická normalizace určuje materiálový prefaktor. Časový potenciál je multiplikátor s nulovou konjugovanou hybností. Kovariantní hybnost se transformuje se spinorovou fází, takže Hamiltonián je gauge invariantní. Rovnice kontinuity a rovnice toku zachovávají Gaussovu vazbu: nejde pouze o jednorázové algebraické vyrušení.

Kladná spinorová norma neimplikuje kladnou energii. Volný Diracův symbol má obě energetické větve. Následující rodina počátečních dat přetrvává po Gaussově redukci i po podmínce Coulombovy kalibrace; nemusí být stacionární při interagujícím vývoji.

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

## 6. Přesná energie neomezená zdola při pevném nenulovém náboji

Zvolíme uvedený normalizovaný vlastní vektor záporné energie pro hybnost podél prostorové osy. Vynásobíme jej reálnou gaussovskou obálkou a rovinnou fází. Hustota náboje je pro každou hybnost stejná gaussovská funkce; tentýž tok tedy řeší Gaussovu vazbu pro celou rodinu. Potenciál může v čase udržovat Coulombovu kalibraci, jeho vazbový multiplikátor však na ploše vazeb z energie vypadne.

Derivace obálky přispívá integrálem totální derivace, který mizí. Materiálová energie se proto rovná záporné Diracově větvi násobené pevným nábojem, zatímco elektrostatická energie na hybnosti nezávisí. Zvyšování hybnosti činí celkovou energii libovolně zápornou při pevném náboji a pevné šířce. Každá sada dat je hladká a má konečnou energii. Jde o protipříklad dolní meze na ploše vazeb srovnávacího modelu, nikoli tvrzení, že každé řešení exponenciálně roste.

Kladná norma i úplná abelovská Gaussova vazba tedy v tomto srovnání nestačí ke zdravému komutujícímu Diracovu poli. Obrácení celkové energetické konvence neodstraní obě znaménka spektra. Jde o známou nutnost rozlišovat klasický komutující spinor od fermionového kvantového pole, zde ukázanou se zachovanou nábojovou vazbou. Nevylučuje to samostatně odvozenou kvantovou statistiku UBT, jiné vazby, redukci fyzikálního sektoru ani jinou dynamiku. Omezení na kladné frekvence by samo vyžadovalo zdůvodnění a zachování lokálními interakcemi; zde dodáno není.

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

## 7. Co se tím zpřesňuje v programu UBT

Konstruktivním výsledkem je úplný podmíněný Gaussův generátor s objemovým i okrajovým členem a explicitní nenulová data s konečným tokem. Překážka je stejně konkrétní: tato vazba neopravuje energii neomezeného komutujícího Diracova pole. Jde o tvrzení pro určený srovnávací model, jehož nezávislý kanonický tok nebyl získán z architektury jediného pole Theta.

Pro kanonickou UBT je dalším nutným objektem úplný předsymplektický proud a lokální generátor po dosazení vybrané kompozitní tetrády a konexe, včetně jejich variací. Musí určit okrajový sektor, fyzikální statistiku nebo redukci na kladnou energii a působení kandidátní fáze na reálný kofrámec. Dokud nejsou tyto objekty odvozeny, nevybírá fundamentální Hamiltonián ani Diracova norma, ani srovnání toku. Z této poznámky neplyne nový potenciál ani pozorovatelná veličina.

<!-- BILINGUAL-UNIT: full-gauss.verification -->

## 8. Ověření a zdroje

[full_gauss_checks.py](full_gauss_checks.py) obsahuje 19 cílených testů. Přesné kontroly SymPy 1.14.0 pokrývají znaménka generátoru, integraci per partes včetně povrchového členu, gauge kovarianci, gaussovskou normalizaci, divergenci, počátek a tok, dva výpočty energie a zápornou Diracovu větev. Nezávislé postupy Python 3.12 používají 50 vzorků vlastních vektorů počítaných přímo komplexní aritmetikou a Simpsonovu kvadraturu se 4096 intervaly doplněnou o Coulombův chvost; tolerance energie je 1e-10. Testy kódují uvedené podmíněné identity, nikoli odvození dynamiky UBT. LEAN-PENDING: Lean a Lake v tomto prostředí chybí; zkompilovaný formální důkaz není přiložen.

Celý audit nyní obsahuje 51 testů. Zdrojem překladu je angličtina; párové rovnice, kód, čísla, struktura i výhrady jsou synchronizovány. Strojové signatury nepotvrzují lidské významové posouzení. Stav sloučení repozitářů, včetně starších nesloučených PR a jejich konkrétních překážek, je v [merge_state_2026-10-25.json](merge_state_2026-10-25.json).

Podkladové odkazy jsou David Tong: [kapitola QFT o Maxwellových vazbách a gauge symetrii](https://www.damtp.cam.ac.uk/user/tong/qft/qfthtml/S6.html) a [kapitola o Diracově kvantování a statistice](https://www.damtp.cam.ac.uk/user/tong/qft/qfthtml/S5.html). Výslovné konvence, gaussovská data a výpočet energie při pevném náboji výše jsou odvozeny zde. Známá otázka Diracovy statistiky není vydávána za nový fyzikální objev.

```sh
python -B -m unittest discover -s audits/scalar_g -p '*checks.py' -v
```
