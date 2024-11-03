## Přepínání scén za běhu (kde a jak)
  - [x] Základní scéna
  - [x] Scéna s lesem
  - [x] Scéna se čtyřmi kuličkami
  - [x] Scéna pro demonstraci použití všech shaderů (Konstantní, Lambert, Phong a Blinn)

  - Sceny implementuji pomoci tridy Scene, ze ktere dedi jednotlive sceny, ktere nasledne zobrazuji

## Světlo (kde a jak máte naimplementováno, jak se updatuje změna světla)
- [x] Světlo

- Svetlo implementuji ve tride Light
- Update svetla provadi trida ShaderProgram, ktera slouzi jako observer na tuto tridu (metoda onLightUpdate)

## Základní třídy (ShaderProgram, DrawableObject, Camera, Controller) (kdo zodpovídá za vykreslování, kde jsou uloženy modely, shadery atd.)
- [x] ShaderProgram
- [x] DrawableObject
- [x] Camera
- [x] Controller

- ShaderProgram slouzi jako observer na tridu Light a Camera, ktera je zodpovedna za jejich updates
- DrawableObject provadi transformace a vykresleni objektu
- Camera slouzi k nastaveni pohledu na sceny
- Controller slouzi k ovladani pohybu kamery, zmene scen a zmene shaderu

## Transformace (Composite pattern) (Máte pro transformace základní třídy? Co a jak jste použili?)
- [x] Transformace
- [ ] Composite pattern

- Transformace mam pouze v jedne tride - Transformation - z duvodu nedbaleho precteni zadani

## Základy OOP
- [x] Encapsulation (zapouzdření) (Kde a jak?)
- [x] Inheritance (dědičnost) (Kde a jak?)
- [x] Polymorphism (polymorfismus neboli mnohotvárnost) (Kde a jak?)

- Encapsulation:
  - Napr v tridach DrawableObject, Model, ... jsou dulezite atributy private a jsou pristupne pouze pomoci metod nebo pripadne vubec
- Inheritance:
  - Hlavni trida Scena, ktera slouzi jako rodic pro jednotlive sceny, ktere jsou nasledne zobrazovany
- Polymorphism:
  - Mam vytvoreno nekolik interfaces, ktere nasledne implementuji v jednotlivych tridach
  - Dve z techto interfaces slouzi jako observer na tridu Light a Camera, ktera je zodpovedna za jejich updates (implementovano v tride ShaderProgram)

## ShaderLoader
- [ ] ShaderLoader

- Podcenil jsem narocnost ukolu - nestihl jsem
