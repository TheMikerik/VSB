# **Poznámky ze všech prezentací:**
### **Internet definice:**
Globální informační systém nebo-li veřejně přístupná "síť sítí", která je logicky propojená prostřednictvím unikátního adresového prostoru - vnitřní sítě založené na protokolech IP (AppleTalk, IPX/SPX), zajišťuje komunikaci s TCP/IP, zajišťuje služby vyšší úrovně. Šíří data v elektronické podobě prostřednictvím "packet switching".

Internet vs. internet - Globální informační a komunikační síť vs. technologicky propojené poč. sítě jako intranet, extranet a ofc internet

**WWW:** Množina propojených dokumentů a zdrojů (hyperlink, URL), tedy propojené hypertextové dokumenty, které zobrazují text a multimédia. URL identifikuje dokumenty. Vzhled přes CSS. Statické a dynamické weby (klient - Javascript, CSS, Applety a server - SSI, PHP, Java).

### **Problémy internetu:**
- Málo IPv4 adres bo IPv4 má pouze 32 bitů. Plýtvají se napiču rozdělováním. Řešíme s CIDR (lepší rozdělování) a NAT (překládáním adres).
- Správa a údržba celkem gg
- Jmenné prostory DNS (např. google.com = nějaká ip)
- Rychlost připojení, cena, garance a přenos multimédií (multicastem)
- Vyhledávání informací bo Google jde do sraček xddd
- Standards a jejich dodržování
- Svoboda, cenzura, bezpečnost a soukromí, spamy, reklamy, právo a vlastnictví, sociální aspekty

### **Budoucnost:**
- Optika
- IPv6 - 128 bit adresy
- Všechno more na telefon
- Zvýšení bezpečnosti
- Přenos multimédií (Selectable QoS, multicast)
- IoT, embeddy

### **TCP/IP:**
- IP identifikuje komp, port identifikuje appku v kompu
- Vrstvy od shora dolů: Aplikační, transportní, síťová, rozhrání nebo také linková vrstva

### **HTTP:** Bezestavový a ukládá si cookies u klienta. Funguje takto:
1. Najebeš adresu do vyhledávače
2. Prohlížeč otevře socket u tebe a připojí se na socket u serveru
3. Na server pošleš automaticky GET
4. Server pošle zpátky html (web) nebo-li ODPOVĚĎ
5. Oba sockety se zavřou

Požadavek GET obsahuje HLAVIČKU ( tedy cestu (absolutní), http verzi, hosta ), agenta (prohlížeč), cookies a co akceptuje (např. to html, xml atd.) nebo jazyky a charakterovou sadu. Klient musí podporovat cache, perzistentní spojení, 100 == continue a akceptovat chunked data.

Požadavek POST obsahuje cestu, http verzi, odkud to jde, agent type, typ obsahu (např. aplikaci www) a velikost obsahu (např. když submittuješ formulář).

### **GET vs. POST in depth rozdíly:**
- GET request má v sobě jenom URL a headery zatímco response má v sobě headery a body (obsah toho dokumentu). Parametry se tam řeší v URL za otazníkem. Put, patch a delete fungují stejně jako post
```
URL/login?username=USERNAME&password=PASS
```
- POST má body v requestu i v response, request obsahuje třeba form data nebo json a response má nějaký text a status code.
```
URL/login
headers {
username: USERNAME,
password: PASS
}
```
- GET a POST je téměř to samé až na předávání těch dat. GET nemůže upravovat data, zatím co POST podle všeho může
<br>
PUT má být k přidání informací
GET k získání informací
PATCH k update
DELETE ke smazání
a POST na všechno ostatní
<br>

ODPOVĚĎ obsahuje http verzi, kod, typ obsahu, encoding obsahu, kdo to poslal (jaký server), velikost obsahu, date. Kody:
- 1xx - informace
- 2xx - úspěch
- 3xx - redirekce klienta
- 4xx - error u klienta
- 5xx - error u serveru
Server musí vyžadovat HLAVIČKU (+ if modified / unmodified) since a pak vkládat svou hlavičku Date.

### **HTTP2 multiplexuje požadavky, kompresuje HLAVIČKY, binární protokol, vylepšená bezpečnost a cache pushing**

**URI:** obsahuje URL a URN. URL je cesta (http, ale třeba i ftp a podobné protokoly), URN je nějaké hovno, kde je taky cesta, ale nejsou tam lomítka, spíš dvojtečky (namespace specific string) a používá nějaké jméno k identifikaci (namespace id).
URN jinak: jmenný prostor, sloužící k oddělení různých množin specifikačních elementů skrze prefixy.

### **Internetové aplikace:**
Vysoká přístupnost, nižší náklady na údržbu atd., klient server. Dělají nějaký úkol pro usera.

**Komunikace:** Server (pasive/active) s klientem (active) nebo peer2peer.

### **Klienti:**
- Tlustý (thick, fat): aplikace u klienta, takže server chilluje, funguje i offline.
- Tenky (thin): u klienta jen basic rozhrání na hardwaru, logika a vše pro appku je na serveru. Menší náklady a lepší bezpečnost. Např. vzdálená plocha.
- Hybrid: OS ze sítě, ale logika u klienta. Redukce nákladů a podpora periférií.
- Chytrý (smart): kombo tenký a tlustý. Lokál zdroje a konektivita se serverem. Aplikace hosta.

### **HTML vs. XHTML:**
XHTML jen párové značky a o něco blíž k XML.. také zákaz křížení značek a a tagů. HTML má problémy s kompatibilitou na zařízeních (zpětně). Oba se validují (zda syntax - sémantika je correct).

### **HTML5:** Není XML, je multiplatform.
HTML+CSS+JS. Nově: interakce s userem, vizualizace (canvas - 2D kreslení) a multimédia (video tag) atd. WebGL na 3D.
Nové elementy: header, nav, article, aside, section, footer, figure, content, legend, progress, time, command, menu, output
SVG vektorový formát, přístup jak k DOMu a dá se hned modifikovat, má vlastní tag. Vlastní atributy přes data- prefix.
Mikrodata taky novinka.

### **CSS:**
Blokové vs. inline elementy. Boxing model - marginy, paddingy, height, wieght, border.

### **CSS3:**
@media screen and (min-width: 600px) and (max-width:900px)
Taky nově :nth-child a :first-of-type selektory. 3D transformace, animace, RGBA, HSL, gradienty.

### **API:**
Základem ECMAScript5. Asynchronně načítá skripty. Atribut draggable, tedy můžeme držet a pohybovat s něčím.
Geolokace, localStorage, webworkers - tedy vlákna, offline věci jako cache, websockety - obousměrná http komunikcace.
- WEBSOCKETS: obousměrný komunikační kanál, nečeká na event od serveru, má vlastní websocket objekt.
send, onmessage, onopen, onclose, onerror, readystate, send. Nutná podpora na klientu i serveru, kombinuje se s WebWorkers.
- DOM (document object model) velké nároky na čas a paměť, standardně pro práci s XML.
- SAX (simple API for XML) zpracuje XML přímo při jeho načítání, rychlý ale vyšší nároky na samotnou aplikací. Není standard. Volá metody a zpracovávání na začátku a na konci elementu.
- Parser - appka, třída či algoritmus. Zpracovává třeba XML v textu a převádí do DOM, ověřuje syntax a validaci.
- WEBWORKERS: provádí algoritmy na pozadí bez ovlivnění interakce s uživatelem, spouštěné externí JS soubory se synchr. přístupem.
Primární objekt je Worker a ten pracuje na globální úrovni, komunikuje pomocí zpráv postmessage - onmessage, ale nemá přístup k objektům jako window, document a parent.
- Drag and drop: draggable="true", onddragstart, ondrop, ondragover. Pracuje s objektem eventu, např. .setData, .getData.
- Drag-In: Možnost přesunutí objektu z PC do prostoru web. stránky. Nutné zachytit událost ondrop na odpovídajícím elementu.
Poskytuje objekty File, FIleList, Blob, FileReader, URL. Přístup k souborům textově, binárně, Base64.
- FileSystem API: rozšiřuje file o BlobBuilder, FileWriter, DirectoryReader, LocalFileSystem, FileEntry či DirectoryEnty.
Využívá virtuální souborový systém - sandbox pro přístup pomocí metody requestFileSystem(), vhodné pro binární data, upload souborů offline práci, mezi uložiště multimédií.
- Geolokalizace: možnost získání latitude, longtitude, altitude, accuracy, speed a timestamp - souřadnice usera.
Podmíněné povolením od usera, závislé na internetu a technických možnostech zařízení. Objekt navigator.geolocation a metody getCurrentPosition a watchPosition.

### **JavaScript:**
Multiplatformní, závislý na prohlížeči,
OOP ale be tříd, case-sensitive,
beztypový. Umí funkcionalitu i vzhled.
Ukládá a čte cookies, spolupracuje s Applety.
Neumí vektor. grafiku, pracovat se sítí,
číst a zapisovat PC soubory, autentikaci,
spouštět appky v OS.

### **DOM:**
Objektově orientované XML a HTML.
API rozhrání abychom mohli k elements
přistupovat jako na objekty. Datová
struktura stromu.

### **TypeScript:**
Třídy a dědičnost, moduly, interfacy,
generika. Kovariance a kontravariance,
statické dat. typy. IntelliSense, refactoring, zvýraznění chyby v IDE.

### **CSS preprocesory:**
Sass, Less, ...
přidávají např. proměnné, mixins (definujem si funkce),
zanořené selektory, matematické operace s barvama atd.

### **AJAX:**
Async JS a XML. Mění webovou stránku skrze HTTP požadavky bez aktualizace celé stránky.
Větší user comfort a efektivita. Malé nároky na přenesení dat, ale eliminuje tlačítko zpět v prohlížeči a stránka není actually editovaná.
```
http_request = new XMLHttpRequest();
http_request = new ActiveXObject("Microsoft.XMLHTTP");
```
máme funkci zpracuj(request):
```
function zpracuj(http_request) {
    if (http_request.status = 200) alert("gratuluji");
}
```

### **Async přístupy:**
- polling: klient se furt připojuje a odpojuje dokola jako kokot a buď dostane no message nebo event při eventu
- long-polling: klient se připojí a čeká, dokud se nestane nějaký event. pak musí dát reconnect a zas.
- streaming: push přístup, např. Comet nebo reverse AJAX, různé techniky a implementace, ale
v podstatě jeden connect a může se stát několik eventů na jeden request.

### **Async:**
EventListener, Callbacks, Promise, async/await

### **XML:**
- eXTensible Markup Language.
- Taky má semantické značky (metaznačkový jazyk narozdíl od HyperText), ale rozděluje dokument podle struktury a identifikuje části dokumentu.
- Názvy elementů a atributů tvoří autor dokumentu.
- Může být stoprocent ASCII. Nemá patent ani copyright, detailní dokumentace W3C, podpora v programovacíh jazycích a nástrojích.
- Data mohou být v elementech nebo v atributech elementů.
- Taky je tu namespace / jmenný prostor (URN).
- Stromová struktura, nesmí se překrývat či křížit.
- DTD - Document type definition je specifikační jazyk pro popis pravidel a možnosti tvorby XML - seznam elementů, atributů, jejich obsahy a vztahy mezi sebou. DTD v prologu před prvním elementem XML.
(ANY, EMPTY - pro obsahy elementů) Nevýhody - neřeší a nepodporuje jmenné prostory, neumožňuje specifikovat datové typy pro obsahy elementů a atributů.
- XSD dělá to samé co DTD ale i ty datové typy, defaultní a pevné hodnoty elementů a atributů, dětské elementy + počet a pořadí.

### **XPath:**
Cesta nebo-li Path Expression je hlavní konstrukční prvek pro specifikaci dotazů.
Obdoba cesty ve files OS, / či //.
Spojování s pipe symboly. Každý krok se skládá z identifikátory osu (axes), testu uzlu a predikátu.
Vyhodnocujeme cestu zleva do prava relativně k uzlu.
Nespecifikovaný uzel je child nebo podle osy. Osy mohou být ancestor, parent, self, child, descendat. Zleva od parent preceeding a z nich preceeding sibling. Zprava od parent following a following-sibling (něco jak teta a strejda v rodokmenu).
Ancestor, descendant, following, preceeding a self dohromady tvoří všechny uzly dokumentu bo se překrávají (kroužkují se rodiče a děti).
text(), node(), comment(), processing-instruction()
Podmínky je možné tvořis s ohledem na literally všechny prvky které mají vztah k našemu elementu.

### **JSON:**
Kolekce párů název a hodnota. Seznam hodnot. Datové typy JSON String/Number/Boolean/Null
```
[
    {
        "name":"darin",
        "user":"astra3"
    },
    {
        atd
    }
]
```

### **Storage:**
Náhrada za cookies - data se neposílají při každém requestu, ukládá se víc dat, přístup pouze autorem dat a napojení eventů.
Princip uložení je klíč a hodnota (String).
**LocalStorage** a **SessionStorage**. Local ukládá bez omezené doby platnosti. Session na jednu session. Přístup přes indexy či rozhrání.
**WebDatabase** - WebSQL Database vs. IndexedDB
**Web:**
- API aby uložil data na straně klienta databázově relačně (SQL)
- Není standard HTML5
- openDatabase(), transaction(), executeSQL()
**Indexed:**
- Řešení pro ukládaní hodně strukt. dat
- Rychlé hledání indexováním
- Sync i async
- Objektově transakční, klíč / hodnota (objekt)
- objekt indexedDB

### **Offline:**
SNižuje nároky na rychlost a přenos dat.
Cache manifest (soubor s definicí cache pravidel např.) - CACHE, NETWORK (tyto soubory nebudou cachovany), FALLBACK (náhrada za necachované soubory)
Aktualizace vyčištěním cache, programově či změnou manifestu.

**Přístup k hardware:** Orientace a poloha zařízení v prostoru, kamera, mikrák, hlas vstup, gesta doteků, fullscreen, ...

### **Grafika:**
- Canvas - bitmap, musí mít uzavírací element. Nad elementem se vytváří kontext, metoda getContext("2d"), kreslí se postupně, animace pak pomocí setTimeout a setINterval, ideálně pomocí requestANimationFrame využívající standard animační smyčku.
- SVG - vektor, modifikace DOM - specifického XML, možnost vazby vizuál elementů na eventy v JS
- WebGL - 3D, kontext "webgl"

Mobilní appky se řeší s abstrakcí a phone API pro native.

### **Web design trendy:**
- obsah na prvním místě
- responsive
- fixed a floating prvky
- flat a zakulacený design, průhlednosti, stínování, animace
- infinite scrolling a single page design
- typografie a velkoformátové fotky

### **Bezpečnost:**
**Definice kyber kriminality:**
- Trestná čínnost páchana za pomoci inf. a komunik. techn.
- Trestné činy proti důvěrnosti, integritě, dostupnosti poč. dat a systémů
- Trestné činy se vztahem k počítači či se vztahem k obsahu počitač
- Trestné činy související s porušením autor. překrávají

1) SQL injekce: ```something' or 2>1```

2) XSS:
```
http://stranka.php?nadpis=cokoliv<script>alert('Toto je úspěšný XSS útok.');</script>
```
- DOčasný/okamžitý/persistentní.
- Eliminace skriptování a filtrace vstupů - řešní.

3) CSRF:
- Skryté volání požadavků na danou funkcionalitu
mezi stránkami (záložkami).
- Nutná znalost prostředí, na které se útočí, často v
rámci autorizovaného přístupu.
- Kombo s XSS.
- Tajné tokeny na serveru a opatrnost uživatele - řešení.

4) Brute force:
časově náročné, řešíme omezení počtu a času pro opakování požadavků a složité údaje.

Pak SPAM, malware, phishing, Ddos a botnety.

### **Frameworks:**
- pro efektivní webdesing, práce s typografií, tvorba layoutu, uživatelské ovládací prvky, rozšiřujicí knihovny a podpora multiplatform.
- FOundation, Bootstrap
- Výhody - rychlý vývoj, nativní podpora CSS preprocesorů, podpora témat, optimalizace přes composite construction, implementace common prvků
- Nevýhody - z určitých pohledů komplexní, vazby na celou řadu nástrojů
BOOSTRAP: nativní a uživatelské stylování, např. grid,
velký výběr prvků, data-, aria- atributy, atribut "role" pro přístupný web.
RŮzné pluginy např. Carousel, Toast.

**Frameworks:**
ROzšiřuje JS. Pluginy na animace, AJAX, DOM.
ROzdělíme na JS knihovny (JQUery), RIA frameworky

např. Vue, Angular atd.

V JQuery je $ funkce, žádný weird syntax.
Např.
```$("a").click(function()) {
    alert("Neklikej na weird odkazy")
}
```












# **Coding části testu:**
### **Basic JS na opáčko:**
**Potřebný JS code na testu:** access k elementům a basic commands:
```
document.write("Hello");

var paragraph1 = "ahoj"
document.write(paragraph1);

if elsy, loopy atd napsat prostě jak C 

var pole = ["a", "b"]
var pole2 = new Array("c", "d")
document.write(pole2.valueOf());

datum = new Date();
alert("Ahoj");

paragraph2.firstChild.nodeValue="Ahoj";
element.innerHTML="<strong>Ahoj, ale délší a tlustší</strong>";

var selectedElement = document.getElementByID('box');
```
nebo getElementByClassName

řešení myši:
```
<tag onmouseover="funkce()" onclick="funkce()" onmouseout="funkce()">...</tag>

document.policko.value.length == 0;
```

řešení submit:
```
<tag onsubmit="funkce()">...</tag>
```

úprava atributu:
```
document.image.src="mojeURL.cz"
```

objekt:
```
var car = {name: "Honda", model: "Civic"}

function() {
    return něco;
}

var car1 = new Car("Škoda", "Fabia");
```

V JQuery je $ funkce, žádný weird syntax.
Např.
```
$("a").click(function()) {
    alert("Neklikej na weird odkazy")
}
```





## **Testy - JS, CSS, XPATH atd.:**
1. css button co ma highlight ma mit zluty background a tucny text
```
button {
    background-color: yellow;
    font-weight: bold;
    box-shadow: 0 0 10px rgba(255, 255, 0, 0.6);
}
```
(box shadow na highlight bo jinak nechápu jak to má být? kdyžtak button:onhover ještě (změnit background color))

2. js span s class box a pridat onclick event
```
const span = document.createElement("span");
span.className = "box";
span.onclick = () => {
    alert("Box clicked!");
};
document.body.appendChild(span);
```

3. xpath knihovna s atributem rok kde hodnota roku je 2022
```
//library[@year='2022']
```
<br><br>



4. Vytvořte (js) element odkazu, odkaz bude ukazovat na vsb, bude mít text VŠB, a přidejte do elementu s id container
```
const link = document.createElement("a");
link.href = "https://www.vsb.cz";
link.textContent = "VŠB";
document.getElementById("container").appendChild(link);
```

5. Napište css které bude měnit barvu textu na modrou všechny h2 které jsou v section s třídou container
```
section.container h2 {
    color: blue;
}
```

6. Napište XPath selector (a bylo tam xml a co máš selectnout)
```
//book/title | //author/name
```
(selects the title of books and name of authors from an XML document)
<br><br>



7. Napište css pro obrázek, který bude mít červenou border a nemá identifikator a nachází se v nějakém elementů (byl specifikovaný) s třídou obrazec
```
.obrazec img {
    border: 3px solid red;
}
```

8. Napište css pro první li, kdy bude text modrý a bude uvnitř ul s zase nějakou specifikovanou třídou
```
ul.some-class li:first-child {
    color: blue;
}
```

9. Napište JS kdy máte obrázek s src menu.png a když na něho najedete tak se jeho src změní na menu-on.png po vyjetí se změní zpátky na původní obrázek.
```
const img = document.createElement("img");
img.src = "menu.png";
img.onmouseover = () => img.src = "menu-on.png";
img.onmouseout = () => img.src = "menu.png";
document.body.appendChild(img);
```

10. Xpath na nalezení všech elementů  možnost s hlas větší než 10
```
//*[@option='hlas' and text() > '10']
```





11. ⁠css kde musis dat velikost textu o 20% vetsi nez nadrazeny tag a ma byt pouzitelna jen pro span s idckem ??? kdy to je v divu
```
div span#neco {
    font-size: 120%;
}
```
(Sets the font size to 120% for a span with the ID "neco" inside a div)

12. ⁠css kdy je pozadi obrazek a cervene pismo, pri najeti ma byt pismo tluste
```
.red-text {
    font-weight: normal;
    background-image: url('your-image.png');
}
.red-text:hover {
    font-weight: bold;
}
```

13. ⁠js kdy pri odeslani formu musis checknout jestli input s idckem jmeno neni prazdny, pokud je tak vyhodit alert
```
const form = document.querySelector("form");
form.onsubmit = (e) => {
    const input = document.getElementById("id");
    if (!input.value.trim()) {
        alert("Input cannot be empty!");
        e.preventDefault();
    }
};
```

1⁠4. vyselectit textove hodnoty z xpath moznosti
```
//option/text()
```