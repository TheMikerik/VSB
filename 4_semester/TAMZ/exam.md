# TAMZ Zkouska

## 1. Prezentace
- Present HTML5 Dev
  - ANDROID: Java, Kotlin
  - iOS: Objective C, Swift
  - Desktop: C, C++, C#, Java

- Sandbox model
  - Zpusob, jakym chranit zarizeni pred skodlivym kodem
  - Aplikace bezi jen v uzavrenem prostredi, ktere ma pristup jen k omezenym zdrojum
  - Aby aplikace mela pristup k citlivym zdrojum, musi to tak byt nastaveno uzivatelem

- CDC vs CLDC
  - CDC je podmnozina JavaSE + dalsi extra classy
  - CLDC je podmnozina CDC
  - CDC (Connected Device Configuration)
    - Pro zarizeni s vetsim obsahem pameti, rychlejsimi procesory a s dobrym internetovym pripojenim
    - Vhodne pro automatizaci + automotivove a zabavni systemy
    - Umoznuje portovat desktop appky na mobilni zarizeni s CDC
    - Virtual machine: CVM

  - CLDC (Connected Limited Device Configuration)
    - Pro zarizeni s limitovanou pameti, pomalymi procesory a s prerusovanym pripojenim k siti
    - Typicke pro mobily nebo PDA (Personal Digital Asistent)
    - Virtual machine: KVM
  - Rozdily v Jave pro CLDC
    - nepodporuje float
    - nepodporuje funkci finalize() kvuli slabemu CPU
    - Maly set pro error handeling


- Profily
  - Sety konfiguraci funkci pro urcite zarizeni
  - Konfigurace + CVM / KVM

## 2. Prezentace
- OTA (Over The Air)
  - Umoznuje instalovat software bez nutnosti budto pripojeni zarizeni k PC nebo vlozeni pametove karty
  - OS / Software updates
  - Skrze Wi-Fi / Data / (kdysi i bluetooth)

- HTML
  - Atributy
  - Odkazy: #id, .class
  - Listy: ul, ol, li

## 3. Prezentace
- BOM
  - Browser Object Model
  - Default browser window that references other objects
- DOM
  - Document Object Model
  - Accessing document elements

- HTML5
  - High Level GUI (UI elements, widgets, inputs, ...)
  - Low Level GUI (Direct input - mouse, clicking, touching)

  - Web storages
    - LocalStorage - without expiracy
    - SessionStorage - lost when the session is exited
    - Stored in key-value format
