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