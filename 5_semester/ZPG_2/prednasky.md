# Prednaska 1
- Skalarni soucin (DOT)
  - Proc se pouziva?
    - V pripade ze jsou normalizovane, tak vraci cos danych uhlu, coz je zaklad vypoctu osvetleni daneho bodu
-


# Prednaska 3
Promitani
  - Rovnobezne
    - Nedeformuje modely, zachovava jejich realne delky
    - Napr v krychli josu vsechny hrany stejne dlouhe
  - Stredove (Perspektivni)
    - Zkresluje modely
    - Pracuje s perspektivou
    - Casti modelu, ktere jsou dale, vypadaji mensi
  - Vyplati se projektivni prostor?
    - 1 bod, 1 vektor, 1 transformace
      - ne, vice operaci
    - 1 bod, 1000 vektoru, 1 transformace
      - ne, vice operaci
    - 1000 vrchol, 1 transformace
      - ne, vice operaci
    - n vrcholu, m transformaci
      - ano
  - Modelove transformace
    - translace, scale, rotace a jejich kombinace


# Prednaska 4
- Skalarni soucin
  - Vysledkem je skalar (cosinus uhlu)
  - Cosinus neni linearni fce
  - Pokud je svetlo primo nad povrchem, tak to vrati 1
- Osvetlovaci modely
  - Konstantni
    - Kazda scena bude mit konstantni osvetleni
    - Ambientni slozka zabranuje tomu, aby nebyly zcela cerne i casti objektu, na ktere nedopada svetlo
  - Lambert
    - I = max(dot(lightVector, worldNor), 0.0)
      - Toto vyradi zaporne hodnoty (budto hodnoty z dot (skal. souc.) a nebo 0)
      - lightVector - vektor mezi povrchem a pozici svetla
      - worldNor - normala
      - obe slozky DOTu musi byt normalizovane
    - Cim mensi je uhel mezi worldNorm a lightVector, tim vetsi intenzitu ma dane svetlo
  - Phong
    - I = Ia + Id + Is
    - Ia (ambient)
      - Cast, ktera osvetluje model i pokud na nej nedopada svetlo
    - Id (difuni)
    - Is (spekularni / zrcadlova)
      - Pocita cosinus odrazeni dle fragmentu vzhledem ke kamere
      - Cim vice jde vektor odrazeni mimo kameru, tim mensi je honota jeho DOTu
    - Vzorec ze strany 22
      - Ia ambientni slozka (obvykle se zadava pouze jednou)
      - Ra sila odrazu
      - Suma pres vsechny svetla
        - intenzita difuzni slozky
        - koeficient odrazu
        - cos uhlu normalu a smerem ke svetlu
        - cos uhlu mezi odrazenym uhlem ke kamre
  - Blinn
    - Upraveny phong
    - Half vector a normaly

# Prednaska 5
- Mame trojuhelnik o vrcholech V1, V2, V3, ktery ma v kazdem vrcholu normalovy vektor n1, n2, n3. Prevedte objekt z local space do world space. Jak prevedeme vrcholy a jak normaly?


# Random fakta
- Ma normala pozici?
  - Nema. Je to vektor. 
  - Jakozto vektor ma pouze smer a velikost
- Suzi smooth vs flat
  - Flat ma vsechny 3 normaly v trojuhelniku jdouci stejnym smerem
  - Smooth ma kazdou normalu v trojuhelniku vypocitanou dle okolnihc trojuhleniku
- Camera space
  - vime kde je kamera [0, 0, 0] - tudiz nemusime posilat pozici kamery a updatovat ji