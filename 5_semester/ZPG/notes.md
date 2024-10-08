# ZPG
## Cvičení
## Přednášky
### Přednáška 2
- Shader
  - Počítačový program určený pro řízení vykreslovacího řetězce (GPU)
  - Vertex shader
    - provádí transformace
    - mění poplohu vrcholu, nemůže mazat ani přidávat vrcholy
    - nemá informace o tělese (nezná sousední vrcholy)
    - používá homogenní souřadný systém (x, y, z, w)
    - rasterizace - provedeni vypoctu, ktery nasledne prevede z vektorove grafiky objekt na rastrovou
    - gl_Position - speciální proměnná, do které nastavujeme výslednou pozici
  - Fragment shader
    - provádí výpočet výsledné barvy pixelu
    - může obsahovat pozici, barvu, normálu atd
    - pixel se může skládat z více fragmentů
    - gl_FragColor - speciální proměnná, do které nastavujeme výslednou barvu (rgba)
  - VAO, VBO

### Přednáška 3
- Transformace
  - Skalár
    - Velicina, ktera je definovana jen velikosti (hmotnost, objem, velikost)
  - Bod
    - Zakladni bezrozmerny objekt, ktery ma jen polohu
  - Vektor
    - Reprezentuje zjednodusene pohyb z jednoho bodu dp druheho
  - Transformace
    - Zobrazeni, ktere kazdemu bodu A priradi jeho bod A'
    - Afinni transformace (Afinita)
      - zachovava rovnobeznosti, linierni zavislosti
    - Posunuti
      - Bodu A pricteme vektor d
    - Zmena meritka
      - Meni velikost bodu v jednotlivych osach
      - Bod A vynasobime
    - Rotace
      - 