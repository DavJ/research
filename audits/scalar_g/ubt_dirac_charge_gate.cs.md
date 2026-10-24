# Pokračování UBT: Diracův náboj, reálná tetráda a kalibrační vazba

## 1. Rozsah a hranice zdrojů

Datum: 2026-10-24. Pracovní matematické porovnání; zde není vybrána fundamentální
akce, fyzikální kalibrační grupa, hmotnost ani normalizace náboje.

[Historický audit skaláru](README.md) nelze automaticky přenést na kanonickou
UBT. Toto pokračování zkoumá konkrétní novější kandidát: reálně lineární mapu ze
sloučeného UBT #724 a zvolený symplektický převod z návrhu UBT #726. Druhý zdroj
byl v **prověřené revizi nesloučeným návrhem**. Zdroje a neměnné revize uvádí
[ubt_reference_sources.json](ubt_reference_sources.json).
[Anglické vydání](ubt_dirac_charge_gate.en.md) má stejný rozsah a odvození.

Předpokládáme komutující reálné souřadnice jedné komplexní matice Theta 2x2,
zvolený pravý sloupcový rámec a uvedený plochý Diracův generátor. Odděleně
prověřujeme algebraické kanonické čtení tetrády. Tím není dokázána vzájemná
slučitelnost čistě levé spinorové transformace a kanonické reprezentace tetrády.
Starý elektromagnetický skalár G zde není identifikován s novou pozorovatelnou
veličinou Theta. Níže použitá bodová kladná norma nedokazuje dolní omezenost
Diracova Hamiltoniánu.

## 2. Dva účinky fáze

Zvolenou mapu a informaci o jejím inverzním převodu zapíšeme jako

$$
\Theta=[\psi,\chi],\qquad
\epsilon=\begin{pmatrix}0&1\\-1&0\end{pmatrix},\qquad
F(\Theta)=u=\begin{pmatrix}\psi\\\epsilon\chi^*\end{pmatrix}.
$$

F je reálně lineární bijekce, nikoli komplexně lineární mapa. Pro reálné phi
centrální fáze Theta indukuje opačné fáze Weylových složek:

$$
F(e^{i\phi}\Theta)=e^{i\phi Q_A}u,
\qquad Q_A=\operatorname{diag}(I_2,-I_2).
$$

Běžná vektorová fáze Diracova spinoru se naopak převádí na

$$
F(\Theta R_\phi)=e^{i\phi}u,\qquad
R_\phi=\operatorname{diag}(e^{i\phi},e^{-i\phi})\in SU(2).
$$

Po volbě F a jejího pravého rámce je tento převod jednoznačný, protože F je
bijektivní. Samotná volba pravé osy však není vnitřně určená: pravá změna rámce
SU(2) může konjugovat sigma_3 na sigma_1. Vzorce tedy určují vektorovou fázi
kandidáta, nikoli nezávisle odvozené elektromagnetické U(1).

## 3. Hmotnost a momentová zobrazení je rozlišují

Pro kandidát z uvedené revize použijeme reálnou hybnost a hmotnost:

$$
h_D(p)=\begin{pmatrix}-\boldsymbol\sigma\cdot\mathbf p&mI_2\\
mI_2&\boldsymbol\sigma\cdot\mathbf p\end{pmatrix},\qquad
\dot u=-ih_Du.
$$

Přímé násobení dává

$$
[h_D,Q_A]=\begin{pmatrix}0&-2mI_2\\2mI_2&0\end{pmatrix},
\qquad [h_D,I_4]=0.
$$

Centrální fáze Theta proto není symetrií tohoto pevného masivního Diracova
generátoru. Konkrétně pro nenormovaný vektor u=(1,0,i,0) platí

$$
\frac{d}{dt}(u^\dagger Q_Au)=4m.
$$

Pro m=0 se axiální fáze v tomto klasickém volném výpočtu zachovává, ale opačné
nábojové váhy zůstávají odlišné od vektorové fáze. Nabitý parametr uspořádání nebo
jiný mechanismus vzniku hmotnosti by vyžadoval vlastní odvození; zde žádný
nevkládáme.

Osm reálných souřadnic uspořádáme jako Re/Im složek psi_1, psi_2, chi_1, chi_2.
Označme J_2=((0,-1),(1,0)), J_8=diag(J_2,J_2,J_2,J_2) a Q reálnou Jacobiho
matici F. Zvolený převod symplektické formy je

$$
\Omega_D=Q^TJ_8Q=\operatorname{diag}(J_2,J_2,-J_2,-J_2).
$$

Použijeme konvenci iota_(Kx) Omega_D=d mu a normalizaci mu(0)=0. Potom
Hessian(mu)=-Omega_D K. Centrální a vektorový fázový generátor dávají

$$
\mu_C=\tfrac12(\|\psi\|^2-\|\chi\|^2),\qquad
\mu_Q=\tfrac12(\|\psi\|^2+\|\chi\|^2).
$$

Oba fázové účinky zachovávají Omega_D; zachování symplektické formy neznamená,
že oba zachovávají zvolený Hamiltonián. Ani jedno momentové zobrazení není
historickou divergencí G.

## 4. Zachování metriky neznamená zachování reálné tetrády

Na kanonickém Lorentzově řezu v Pauliho bázi platí

$$
E_\mu=i e_\mu^0I_2-i e_\mu^k\sigma_k,\qquad E_\mu^\dagger=-E_\mu,
\qquad
\tfrac12(E_\mu^\sharp E_\nu+E_\nu^\sharp E_\mu)=g_{\mu\nu}I_2.
$$

Sharp je zde komplexně lineární kvaternionová konjugace reprezentovaná
adjugovanou maticí 2x2, nikoli hermitovské sdružení. Při **předpokládaném pravém
kovariantním zákonu** E'_mu=E_mu R algebra dává

$$
\tfrac12[(E_\mu R)^\sharp(E_\nu R)+(E_\nu R)^\sharp(E_\mu R)]
=(\det R)g_{\mu\nu}I_2.
$$

R_phi tedy zachovává celou centrální metrickou identitu. Pro reálný časupodobný
bázový prvek E_0=iI_2 však platí

$$
E_0R_\phi+(E_0R_\phi)^\dagger
=\operatorname{diag}(-2\sin\phi,2\sin\phi).
$$

Transformovaná tetráda je obecně mimo pevný antihermitovský řez, přestože její
metrika zůstává stejná. Obecněji zachování tohoto řezu pro každý vektor
nedegenerované tetrády při det R=1 vyžaduje R=+I_2 nebo R=-I_2. Důkaz: z E=iI_2
dostaneme R^dagger=R; tři prostorové bázové prvky pak vynutí komutaci R se všemi
Pauliho maticemi. Tedy R=rI_2 s reálným r a det R=1 vynutí r^2=1. Kontrolní
skript nezávisle řeší reálné lineární podmínky: hodnost sedm v osmi reálných
prvcích, následovaná determinantovou podmínkou.

Jde o překážku pro **jednoduchý pravý účinek zachovávající řez**, nikoli pro
každou elektromagnetickou realizaci v UBT. Odvozené rozšíření na kalibrační
orbity by mohlo připustit přesun reálných reprezentantů mimo zvolený řez při
zachování fyzikální metriky. Závěr by mohla změnit také odvozená kompenzační
transformace. Zvolená F však neposkytla její zákon pro konexi, vazby ani fyzikální
čtení. Kanonická architektura se zde nemění.

## 5. Lokální kalibrační redundance potřebuje více než kladné momentové zobrazení hmoty

Na předepsané reálné časové nadploše s pevnou kladnou hustotou je ultralokální
kandidátní symplektická forma hmoty integrálem Omega_D. Pokud se vektorová fáze
stane lokální redundancí **pouze zavedením vazby nulové hladiny momentového
zobrazení hmoty**, bez hybnosti elektrického toku, derivativního příspěvku,
náboje pozadí či nenulové hladiny, pak

$$
\mu_Q(x)=0\quad\Longrightarrow\quad
\sum_{A=1}^{8}(x^A(x))^2=0\quad\Longrightarrow\quad\Theta(x)=0.
$$

Pro hladká pole a konečné lineární kovariantní konexe to dává DTheta=0 a
degenerovanou složenou tetrádu. Toto konkrétní minimální pomocné kalibrační
zavedení proto nemůže popsat nenulové komutující amplitudy Theta.

Předpoklady jsou podstatné. Skutečná Gaussova vazba může obsahovat divergenci
elektrického toku vyvažující náboj hmoty. Vybraná složená konexe může změnit
celou symplektickou strukturu svými indukovanými variacemi. Nenulová hladina
momentového zobrazení může zabránit nulovému řešení, ale její hodnota a fyzikální
význam by byly dalšími údaji vyžadujícími odvození. Nic z toho nepředpokládáme.
Argument se týká běžných komutujících reálných souřadnic, **nikoli** fermionického
fázového prostoru s Grassmannovými proměnnými či normálně uspořádaného kvantového
operátoru náboje. Odvození fermionické statistiky zůstává samostatnou podmínkou.

## 6. Ověření a další rozhodnutí

[dirac_charge_checks.py](dirac_charge_checks.py) poskytuje 14 kontrol: přesné
fázové identity v SymPy, hmotnostní komutátor, obě momentová zobrazení, obecnou
metrickou identitu pravého faktoru, podgrupu zachovávající řez a 50 nezávislých
vzorků fází a vývoje náboje s komplexními čísly v Pythonu. Numerická větev
nepoužívá maticové vzorce SymPy; vzorkování nedokazuje analytická tvrzení.
Formální stav je LEAN-PENDING: Lean ani Lake nejsou v prověřeném prostředí
dostupné a zkompilovaný důkaz v Leanu není dodán.

Všech 32 kontrol skaláru a pokračování spustíte z kořene repozitáře:

```sh
python -B -m unittest discover -s audits/scalar_g -p '*checks.py' -v
```

Dalším konstruktivním požadavkem je **odvozený generátor lokální vazby** pro tuto
kandidátní vektorovou fázi, včetně celé symplektické formy a indukované
transformace tetrády a konexe. Musí připustit nenulová fyzikální data Theta,
zachovat fyzikální metriku a vysvětlit roli reálného řezu. To je přesnější cíl
než přidání nového potenciálu či přejmenování starého G. Fundamentální
Hamiltonián, mikroskopická akce i nová pozorovatelná veličina zůstávají otevřené.

## 7. Odkazy

- Neměnné zdroje UBT včetně sloučeného #724 a prověřeného návrhu #726:
  [záznam zdrojů](ubt_reference_sources.json).
- David Tong, [Quantum Field Theory, kapitola 4](https://www.damtp.cam.ac.uk/user/tong/qft/qfthtml/S4.html):
  standardní Diracovy a Weylovy reprezentace a proudy. Zobrazené převody a
  komutátor jsou zde výslovně vypočteny.
- Ana Cannas da Silva, [Lectures on Symplectic Geometry](https://people.math.ethz.ch/~acannas/Papers/lsg.pdf),
  hamiltonovské účinky a redukce: momentová zobrazení závisí na konvencích a lze
  je posunout o konstanty. Výše jsou uvedeny normalizace a předpoklady nulové hladiny.
