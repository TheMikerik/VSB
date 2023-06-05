# Vypracovane otazky k zaverecne zkousce

# Kontrolní otázky 1

## Co je hlavním motivem pro vývoj programovacího paradigmatu od imperativního k objektovému?
- Paradigma:
    - Styl, kterým se programuje
    - Můžou to být prvky programu (objekty, funkce, proměnné) nebo kroky výpočtů (přiřazení, vyhodnocení, tok dat) 
- Motiv:
    - Modularita
    - Efektivita (dědění, znovupoužití)

## Co je imperativní programování?
- Popisuje, jak se věci řeší a jde se postupně instrukce po instrukci narozdíl třeba od funkcionálního
- Běžně užívané jazyky (C, Python, Java, PHP)

## Co je modulární programování?
- Návrh shora dolů
- Velký projekt rozdělí do menších okruhů
- Moduly (bubliny) jsou rozděleny podle funkčnosti, propojeny na základě závislostí a rozkouskovány na další menší podmoduly, nebudou se navzájem nutně afektovat a přepisovat

## Jaké jsou hlavní faktory kvality software?
- Vnitřní faktory jsou skryty uživateli
- Vnější faktory popisují chování navenek
    - Správnost
        - Míra toho, jak moc program/algoritmus dělá to, co má
        - Robustnost
        - Blbuvzdornost
        - Kontroluje správné vstupy, správné chování programu v hraničních situacích
    - Rychlost
    - Rozšiřitelnost
    - Použitelnost
    - Kompatibilita

## Co je pochopitelnost modulu? Uveďte příklad.
- Všechny úlohy, které modul provádí musí být jasně definované a zřejmé po přečtení code
- Příklad: ez aritmetická operace - program je jasný na pochopení i pro člověka, který ho neprogramoval

## Co je samostatnost modulu? Uveďte příklad.
- Modul musí mít co nejmenší počet závislostí
- Ideálně bychom měli být schopni modul z programu vyjmout a použít v jiném tak, aby všechno fungovalo
- Příklad: soubor funkcí provádějící jisté výpočty můžu použít v libovolném programu

## Co je kombinovatelnost modulu? Uveďte příklad.
- Moduly musí být navzájem kombinovatelné - nedojde k chybě nebo k nějakým potížím, nějaký spor apod.

## Co je zapouzdření modulu? Uveďte příklad.
- Modul si hlídá, ke kterým hodnotám mají ostatní moduly přístup a které jsou soukromé
- Příklad: class KeyValue neposkytuje přímo své hodnoty ale má napsané funkce, které je vrací

## Co je explicitní rozhraní modulu? Uveďte příklad.
- Modul má konkrétně a detailně popsané, jaké předpoklady (vstupy, závislosti) potřebuje pro své správné fungování
- Příklad: funkce násobení nepřijímá jiné vstupy než čísla

## Co je syntaktická podpora modularity?
- Ze zápisu musí být zřejmé, kde začíná a kde končí zápis modulu

## Co je pět kritérií pro dobrou modularitu?
- Dekomponovatelnost
- Kombinovatelnost
- Pochopitelnost
- Kontinuita
- Ochrana

## Co se rozumí pěti pravidly zajišťující dobrou modularitu?
- Přímé mapování
- Pár rozhraní
- Malá rozhraní (weak coupling)
- Explicitní rozhraní
- Skrývání informací

## Popište jednotlivá kritéria dobré modularity. Uveďte příklady.
- Dekomponovatelnost
    - Program dobře rozděluje problém na menší podproblémy
    - Jednotlivé moduly řeší malé problémy a jsou samostatné
- Kombinovatelnost
    - Moduly se dají používat spolu i zvlášť
- Pochopitelnost
    - Člověk dokáže modul jednoduše pochopit bez toho, aby musel rozumět ostatním
- Kontinuita
    - Při malé změně zadání se bude muset změnit jen malé množství modulů
- Ochrana
    - Chyba v jednom modulu se projeví maximálně v pár sousedících modulech a neshodí celý systém

## Popište jednotlivá pravidla pro dobrou modularitu. Uveďte příklady.
- Přímé mapování
    - Vytvořené moduly musí být kompatibilní s moduly definovanými v modelu řešení problému
    - Nesmí znemožnit funkčnost už vytvořeného programu
- Pár rozhraní
    - Moduly by měly komunikovat s minimálním množstvím jiných modulů
- Malá rozhraní (weak coupling)
    - Pokud už moduly musí komunikovat, měly by si vyměnit jen ty nejnutnější informace
- Explicitní rozhraní
    - Musíme jasně vidět, kdy dva moduly komunikují
- Skrývání informací
    - Autor modulu se musí rozhodnout, které informace poskytne autorům jiných modulů

## K čemu je konstruktor? Uveďte příklad.
- Zapíše data do paměti
- Spouští se při deklaraci objektu
- Inicializuje objekt, naplňuje objekt hodnotami

## K čemu je destruktor, kdy ho potřebujeme a kdy ne? Uveďte příklad.
- Čistí paměť
- Není potřeba, když jsou data objektu statická


# Kontrolní otázky 2

## Co je hlavními příčinami potřeby změn software?
- Nové požadavky zákazníka
- Změna systémových komponent
- Security reasons

## Jaké jsou hlavní faktory ovlivňující objektovou orientovanost?
- Objektové techniky pomáhají napsat lépe udržovatelný software
- Patří mezi ně:
    - Metoda a jazyk
    - Implementace a prostředí
    - Knihovny

## Vysvětlete, co rozumíme pojmy objektově orientovaná metoda (přístup) a jazyk.
- Jazyk je pouze prostředek k vytvoření objektově orientovaného programu a OOP dodává jistou míru abstrakce nad programem
- Programovací jazyk a způsob jeho použití
- Způsob uvažování a vyjadřování
- Záznamy
- Přístup / metoda: Způsob programování, který se zaměřuje na práci s objekty. Hlavní myšlenkou objektově orientované metody je modelování skutečného světa a jeho konceptů prostřednictvím objektů.

## Vysvětlete, co rozumíme podporou objektově orientované implementace.
- Podpora vývoje
- Podpora nástrojů pro nasazení nových verzí
- Podpora dokumentace

## Vysvětlete, co rozumíme podporou opakované použitelnosti.
- Podpora toho, aby byly knihovny a řešení použitelné znovu později

## Vysvětlete pojmy třída a objekt a použijte správnou terminologii.
- Třídu můžeme chápat jako část softwaru, která popisuje abstraktní datový typ a jeho implementaci
- Abstraktním datovým typem můžeme rozumět objekty se společným chováním reprezentovaným seznamem operací
- Objekt je instance třídy

## Zdůrazněte vlastnosti třídy z pohledu modularity.
- Třídy nepopisují jen typy objektů, ale musí být zároveň modulární
- V čistém OOP by neměly být jiné samostatné jednotky než třídy

## Vysvětlete princip zapouzdření v OOP.
- Data objektu jsou skryty před zbytkem programu
- Můžeme je získat pouze pomocí členských funkcí

## Vysvětlete princip zasílání zpráv.
- *Feature call*
- Výpočetní mechanismus
- Objektu jako instanci třídy je zaslána zpráva daného jména a s potřebnými parametry - když se provádí nějaká operace na jiném objektu
- V rámci tohoto principu objekty interagují tím, že si posílají zprávy, což je volání metody jednoho objektu z jiného objektu.

## Vysvětlete principy deklarace a definice jednoduché třídy v C++.
- Deklarací naznačujeme, jaké chování objekt může mít - deklarujeme, že nějaký takový objekt existuje
- Definicí podrobně chování specifikujeme - popisujeme metody a jejich průběh


# Kontrolní otázky 3

## Vysvětlete, jak vznikají objekty třídy, pojem konstruktor a principy práce s ním v C++.
- Objekty vznikají jako instance třídy
- Chování při vzniku instance je definováno konstruktorem
- Konstruktor je metoda bez návratového typu a jeho jediným úkolem je vytvořit a  definovat hodnoty atributů objektu
- Je volán automaticky při vzniku nové instance
- Může jich být definováno více (přetěžování metod) - rozlišeny podle vstupních parametrů

## Vysvětlete, jak zanikají objekty třídy, pojem destruktor a principy práce s ním v C++.
- Destruktor specifikuje chování při zániku instance
- Objekty mohou zanikat více způsoby: 
    - Destruktor voláme sami v bloku programu
    - Destruktor se zavolá automaticky při ukončení programu
- V případě, že deklarujeme novou instanci třídy dynamicky, je destruktor volán při volání operátoru delete
- Chování destruktoru můžeme definovat stejně jako konstruktoru

## Vysvětlete rozdíl mezi statickou a dynamickou deklarací objektů v C++.
- Při **statické** deklaraci objektu je celý objekt uložen v zásobníku, objekty jsou vytvářeny při vstupu do oblasti platnosti, po opuštění daného bloku nebo funkce jsou statické objekty automaticky zničeny, statické objekty se inicializují automaticky na výchozí hodnoty (pokud nejsou definovány vlastní konstruktory)
- Při **dynamické** alokaci je v zásobníku uložen pouze ukazatel na adresu v haldě, na níž je objekt uložen, objekty jsou vytvářeny za běhu programu a existují, dokud nejsou explicitně uvolněny, mají explicitní životnost, která není omezena na daný blok nebo funkci, inicializace dynamických objektů musí být provedena buď konstruktorem nebo manuálně po vytvoření objektu

## Jak se dá postupovat, pokud chceme v zadání programu nalézt třídy, jejich metody a datové členy?
- Hledáme v zadání podstatná jména a slovesa
- Prohlédněte si zdrojový kód programu: Zkoumejte zdrojový kód programu a hledejte deklarace tříd
- Prozkoumejte definice tříd: Po nalezení deklarace tříd prozkoumejte jejich definice.
- Zkoumejte vztahy mezi třídami
- Analyzujte metody a datové členy
- Využijte dokumentaci a komentáře

## Kdy a proč potřebujeme použit více konstruktorů jedné třídy?
- Jedná se o vlastnost polymorfismu
- Přetížený konstruktor poznáme tak, že se liší počtem nebo typem parametrů
- Více konstruktorů můžeme použít například když je více způsobů, jak takový objekt vytvořit (viz Account)

## Kdy potřebujeme deklarovat a definovat destruktor?
- Pokud deklarujeme instanci třídy dynamicky

## Co jsou výchozí konstruktory a destruktory a k čemu je potřebujeme?
- Jedná se o konstruktor s prázdným tělem programu 
- Je volán v případě, kdy není definován vlastní

## Jaké typy metod obvykle musíme deklarovat a definovat?
- Getry a Setry, konstruktory a destruktory a metody manipulujicí s objekty

## Co jsou objektové kompozice a k čemu jsou dobré?
- Definujeme třídu využívající jinou třídu, avšak nejedná se o dědičnost
- Například Bank má v sobě seznam Account a seznam Client


# Kontrolní otázky 4

## Jaký je rozdíl mezi funkční a objektovou dekompozicí programu?
- Funční
    - Co bude systém dělat
    - Obsahuje sadu funkcí
- Objektová
    - Kdo bude funkčnost zajišťovat
    - Jedná se o sadu objektů

## Proč preferujeme objektovou dekompozici a jaké jsou hlavní problémy funkční dekompozice?
- Problémy funkční:
    - Špatná rozšířítelnost
    - Neumí to opakovanou použitelnost
    - Neumí to kombinovatelnost
- Proč?
    - Z důvodu, že tyto problémy neobsahuje
    - Objektová je časově stabilnější 
    - Lépe použitelná v budoucnosti

## Za jakých podmínek můžeme považovat třídu za objekt a jak to implementovat v C++?
- Když má třída v sobě nějaká třídní (static) data/metody
- Když je splněno zapouzdření
- Pajdova odpověď:
    - Třídu považujeme za objekt v případě že obsahuje getry a setry.
    - Neboli, dá se s daným objektem manipulovat
    - Implementujeme pomocí public častí třídy

## Vysvětlete rozdíl mezi členskými položkami třídy a instance a popište jejich dostupnost.
- K položkám třídy má přístup jakákoli instance třídy a dá se k nim dostat i bez vytvoření instance
- Položky instance se mezi instancemi nesdílí

## Jak můžeme v C++ důsledně odlišovat práci s členskými položkami tříd a instancí?
- Konvence pro práci s daty tříd
    - Instanční data/metody: voláme instanci a `->`
    - Třídní data/metody: voláme třídu a `::`

## Potřebuje třída v roli objektu konstruktor resp. destruktor a proč?
- Nepotřebuje v kažém případě
- Konstruktor potřebuje v případě, kdy neobsahuje static hodnoty
    - Static hodnoty se musí inicializovat zvlášť


# Kontrolní otázky 5

## Které dva klíčové požadavky řešíme pomocí dědičnosti?
- Znovu-použitelnost: Dědičnost umožňuje vytvořit novou třídu (podtřídu nebo odvozenou třídu) na základě již existující třídy (nadtřídy nebo rodičovské třídy). Tímto způsobem můžeme zdědit všechny vlastnosti (datové členy a metody) nadtřídy do podtřídy a znovu je využít. Podtřída může přidat nebo upravit funkcionality podle svých specifických potřeb, ale zdědí základní implementaci a chování z nadtřídy. Tím se minimalizuje opakování kódu a umožňuje efektivní znovupoužití existujícího kódu.
- Rozšířitelnost (extensibility):
Dědičnost umožňuje rozšíření funkcionality existující třídy tím, že vytvoříme novou třídu, která dědí od této existující třídy. Nová třída (podtřída) může přidávat další datové členy a metody, které jsou specifické pro rozšířenou funkcionalitu. To umožňuje flexibilní rozšíření existujících tříd a snadné přidávání nových funkcí bez nutnosti upravovat původní kód. Tím se zvyšuje modularita a umožňuje snadné změny v programu bez narušení již fungujících částí.

## Jaké návrhové požadavky máme na použití tříd (co s nimi můžeme dělat)?
- Rozsireni, Pozmeneni, kombinovani s jinyma tridama z objektů jiné třídy.

## Jaký je rozdíl mezi dědičností a skládáním? Co mají společného?
- Skládáním docílíme toho, že objekt jedné třídy je složen z vícero podtříd
- Dědičností docílíme toho, že nová třída je rozšířením nebo speciálním případem existující třídy (nebo více tříd).
- Instance třídy potomka obsahuje vše, co má instance třídy předka.

## V jakých rolích vystupují třídy v dědičnosti? Použijte správnou terminologii.
- Nadtřída (nebo rodičovská třída):
Nadtřída je třída, ze které je odvozena jiná třída.
Nadtřída poskytuje obecný a základní funkční rámec, ze kterého dědí podtřídy.
- Podtřídy zdědí datové členy a metody nadtřídy a mohou je případně rozšiřovat nebo upravovat.
Podtřída (nebo odvozená třída):
Podtřída je třída, která dědí vlastnosti (datové členy a metody) z nadtřídy.
Podtřída rozšiřuje nebo upravuje funkcionality nadtřídy a přidává své vlastní specifické funkce.
Podtřída může dědit z jedné nebo více nadtříd, což se nazývá vícečetná dědičnost.
- Bázová třída (base class):
Bázová třída je synonymem pro nadtřídu, ze které je odvozena podtřída.
Je to třída, která poskytuje základní implementaci a funkcionality, ze které dědí podtřída.
- Potomci (descendants):
Potomci jsou třídy, které jsou odvozeny z určité nadtřídy (nebo více nadtříd).
Tedy všechny podtřídy a pod-podtřídy dané třídy jsou jejími potomky.
- Předek (ancestor):
Předek je třída, ze které je odvozena daná třída (nebo více tříd).
Předek je opačným pojmem k potomkovi. Například, pokud třída A je předkem třídy B, pak třída B je potomkem třídy A.

## Vysvětlete v jakém obecném vztahu je třída, ze které se dědí, se třídou, která dědí.
- Předek definuje společné chování všech svých potomků.
- Potomci mohou toto chování rozšířit či pozměnit.

## Co všechno se dědí, co ne a proč?
- Datové členy, metody, konstruktory a destruktory. Nedědí se konstruktory a destruktory s parametry, statické metody a datové členy, přístupové modifikátory

## Co rozumíme jednoduchou dědičností a jak s tím souvisí hierarchie tříd v dědičnosti?
- Každý potomek má právě jednoho předka.
- Předek může mít více potomků.
- V případě jednoduché dědičnosti je touto hierarchií strom.

## Co je Liskové substituční princip a jak se projevuje v dědičnosti?
Podtřída musí dodržovat rozhraní nadtřídy:
Všechny veřejné metody deklarované v nadtřídě musí být také dostupné v podtřídě, přičemž zachovávají stejný vstup a výstup.
Podtřída by měla dodržovat specifikace, smlouvy a předpoklady nadtřídy.
---
Podtřída nesmí způsobovat omezení nebo zúžení chování:
Metody v podtřídě by neměly vyžadovat omezenější sady parametrů nebo vrácených hodnot než metody v nadtřídě.
Podtřída by neměla vyhazovat výjimky, které nejsou povolené v nadtřídě nebo nevyhazovat žádné výjimky, pokud nadtřída je očekává.
---
Podtřída může rozšiřovat chování:
Podtřída může přidat další metody nebo rozšířit stávající metody nadtřídy, aby poskytovala dodatečnou funkcionalitu.
Podtřída může implementovat virtuální metody z nadtřídy s vlastním chováním.

## V jakém pořadí se volají a vykonávají konstruktory při použití dědičnosti?
- 1. Volání konstruktoru objektu.
- 2. Volání konstruktoru předka.
- 3. Vykonání konstruktoru předka.
- 4. Vykonání konstruktoru objektu.


# Kontrolní otázky 6

## Co rozumíme paradoxem specializace a rozšíření?
- Vztah dědičnosti je vztahem obecný - speciální
- Potomek je tedy speciálním případem předka
- Paradoxem je, že při rozšíření toho potomek vždy umí více než jakýkoli jeho předek

## Uveďte správné a špatné příklady vztahu "generalizace-specializace".
- Potřeba rozšíření sama o sobě není dostačující pro použití dědičnosti
- Špatné: bod jako předek a kružnice jako potomek - kružnice není *speciálním* případem bodu
- Dobré: obdélník jako předek a čtverec jako potomek

## Co rozumíme v dědičnosti změnou chování?
- Pokud je chování deklarováno v předkovi, můžeme ho v potomkovi deklarovat znovu
- Existuje pak více metod stejného jména, kde metody mají různé chování závislé na tom, na jaký objekt je voláme

## Co rozumíme přetížením? Jedná se o rozšíření nebo změnu chování?
- Přetížením rozumíme situaci, kdy daná metoda má stejné jméno, ale má jiné parametry nebo jejich typy
- Typicky konstruktory
- Jedná se o rozšíření

## Uveďte různé typy přetížení.
-- Jméno metody zůstává stejné:
- Jiný počet parametrů
- Jiné datové typy parametrů
- Jiná návratová hodnota (ne v C++)

## Co rozumíme překrytím? Jedná se o rozšíření nebo změnu chování?
- Překrytím rozumíme situaci, kdy metoda potomka má stejnou deklaraci, jako metoda předka (stejnou signaturu)
- Potomek dědí i metodu předka. Má tedy dvě metody se stejnou deklarací
- Například metoda na výběr peněz z různých typů účtů v bance
- Jde o změnu chování

## Jaký princip porušujeme, použijeme-li „protected“ a proč?
- Zapouzdření
- Private část předka už není soukromá protože je přístupná i potomkům

## Jaký problém přináší potřeba změny chování v dědičnosti?
- Pokud je chování deklarováno v předkovi, můžeme ho v potomkovi deklarovat znovu
- Existuje pak více metod stejného jména

## Popište, jak se prakticky projevuje různá míra přístupu k položkám třídy.
- Public: přístupná všem
- Protected: přístupná třídě a jejím potomkům
- Private: přístupná jen třídě samotné

## Jak se použití „protected“ projeví ve vztahu předka a potomka?
- Potomek má přístup k určitým hodnotám nebo metodám v private části předka


# Kontrolní otázky 7

## Jaký je rozdíl mezi shadowing a overriding překrytím? Uveďte příklady
- Shadowing (method hiding)
    - Jde o statické překrytí, kdy nová metoda potomka „zastíní“ metodu předka
    - Dílčí chování objektu tedy odpovídá třídě, v jejíž roli vystupuje
- Overriding
    - Jde o dynamické překrytí, kdy se vždy (i v roli předka) použije metoda potomka, pokud ji má implementovanou
    - Dílčí chování objektu tedy odpovídá třídě, jejíž je tento objekt instancí

## Co rozumíme polymorfismem a s čím to souvisí?
- Polymorfismus je schopnost objektu vystupovat v různých rolích a podle toho se chovat
- Kombinuje své chování s chováním předka, jinak se o skutečný polymorfismus nejedná
- Souvisí to se substitučním principem, tedy se zastupitelností předka potomkem

## Co rozumíme polymorfním přiřazením?
- Když je zdroj přiřazení jiného typu než cíl přiřazení

## Co je časná vazba? Uveďte příklady.
- Když překladač při volání metody vyhodnocuje typ instance již v době překladu
- Časná vazba je výchozí - použije se když neoznačíme metodu jako virtual
- Při volání metody předka Withdraw se zavolá metoda CanWithdraw taky od předka a nezáleží na tom, o jaký objekt se ve skutečnosti jedná

## Co je pozdní vazba? Uveďte příklady.
- Potřebujeme zjistit, kdo metodu žádá, ale až v okamžiku volání
- Když použijeme virtual - Shape má svoji virtual metodu Area ale volat se bude ta metoda, která patří Třídě objektu

## Popište, co je virtuální metoda a její vlastnosti.
- Chceme-li aby se rozhodlo, která překrytá metoda bude volána, až v průběhu programu (overriding), použijeme virtuální metodu
- Dáváme překladači najevo, že si přejeme využít dynamickou nebo také pozdní vazbu (late binding)

## Popište, co je tabulka virtuálních metod a jak funguje.
- Jakmile některou metodu definujeme jako virtuální, překladač přidá ke třídě „neviditelný ukazatel“, který ukazuje do speciální tabulky nazvané tabulka virtuálních metod (VMT).
- Pro každou třídu, která má alespoň jednu virtuální metodu, překladač vytvoří tabulku virtuálních metod
- Tabulka obsahuje ukazatele na virtuální metody
- Tabulka je společná pro všechny instance dané třídy

## Může být konstruktor virtuální? A proč?
- Nemůže
- Před jejich voláním není ještě vytvořen odkaz do VMT

## Může být destruktor virtuální? A proč?
- Může
- Můžeme tak ničit objekty bez znalosti jejich typu

## Kdy mluvíme v C++ o polymorfismu a jak se to projeví v návrhu?
- Polymorfismus je spojen s dědičností
- Nemá smysl mluvit o polymorfismu, pokud nepoužijeme virtuální metody (overriding)
- Jde stále o zastupitelnost předka potomkem

## Co je polymorfní datová struktura a k čemu ji využíváme?
- Struktura která obsahuje objekty různých tříd
- Po takto uložených objektech můžeme požadovat (volat) pouze společné metody předka
- Jak volat ostatní metody objektu vráceného v typu předka? Je nutno přetypovat – je to jedno z omezení polymorfismu.

## Kdy potřebujeme virtuální destruktor? S čím to souvisí?
- Když nevíme typ objektu, který potřebujeme zničit

# Kontrolní otázky 8

## Co je čistě virtuální metoda?
- Metoda, která má pouze deklaraci, nemá definici

## Kdy je vhodné použít čistě virtuální metodu? Uveďte příklad.
- Pro správný návrh programu
- Ideální použití jako vzor pro dědičnost potomky

## Co je abstraktní třída?
- Třída, která má alespoň jednu čistě virtuální metodu
- Abstraktní proto, že nemůžeme vytvořit její instanci (protože čistě viruální metoda má sice deklaraci, ale nemá definici/implementaci)
- Může, ale nemusí, mít členské proměnné a implementované metody

## Kdy je vhodné použít abstraktní třídu? Uveďte příklad.
- Když budeme v programu mít dědičnost a budeme chtít předem určit vzor pro potomky

## Má abstraktní třída konstruktor a destruktor? A proč?
- Má konstruktor a destruktor pro potomka

## Může mít abstraktní třída členská data a funkce (metody)?
- Může, ale nemusí, mít členské proměnné a implementované metody

## Co je čistě abstraktní třída?
- Třída, jejíž všechny metody jsou čistě virtuální
- Slouží jako „prázdný“ vzor pro dědičnost
- Deklaruje, ale nedefinuje, budoucí společné chování potomků

## Co je vícenásobná dědičnost?
- Potomek může dědit z více tříd
- Musí se implementovat opatrně, může být nebezpečná a špatně pochopitelná

## Kdy není vhodné použít vícenásobnou dědičnost? Uveďte příklad.
- Když předci mají společný stav nebo chování
- Příklad: když se dědičnost rozdělí a znovu zase sejde

## Kdy je možné použít vícenásobnou dědičnost? Uveďte příklad.
- Potřebujeme-li, aby objekty reprezentovaly v různých situacích různé abstrakce
- Každý potomek je jedinečný a specifický typ předka

## Jaké problémy mohou nastat při použití vícenásobné dědičnosti? Uveďte příklad
- Konflikty jmen
    - Předek může mít stejně pojmenované členské položky (proměnné nebo metody)
    - Dá se vyřešit různými způsoby
- Opakovaná dědičnost
    - Musí se ohlídat, aby se vícekrát nedědilo ze stejné třídy

## Co je opakovaná dědičnost? Uveďte příklady.
- Když se v návrhu stane, že se z jedné třídy dědí vícekrát

## Proč můžeme potřebovat vícenásobnou dědičnost? S čím to souvisí?
- Potřebujeme-li, aby objekty reprezentovaly v různých situacích různé abstrakce
    - Nejlépe dost různé na to, aby nehrozily konflikty jmen
    - Souvisí se zastupitelností předka potomkem
- Ideální je, když jsou předci čistě abstraktní třídy (bez dat)
    - Pak je to totéž jako „interface“