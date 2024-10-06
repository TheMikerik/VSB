# OSY
## Prednasky
### Přednáška 1
- Operační systém je mezivrstva mezi uživatelem a hardwarem.
- Je to jediná cesta, jak se dostat k hardware
- Pohledy
  - Shora (user-os-hw)
    - Unifikované funkce - jednotná sada funkcí, které jsou dostupné všem programům nehledě na zařízení
  - Zdola (hw-os-user)

- Dávkové zpracování (2 a 3 generace PC)
- 3 generace
  - počátek paralelismu (byl přidán timesharing)
- 4 generace
  - PC jak je dnes známe

- Procesy
  - Jakmile někde v počítači běží nějaký kód, tak musí být zabalen v procesu
  - Seznam procesů je v systému veřejný
  - *Jednotka, která se stará o část kódu, který je vykonán*
  - OS se stará o vlánka jako o procesy
  - Jsou uspořádány do stromu
  - Adress Space
    - Každý proces má svůj vlastní prostor
    - Nemohou do sebe zasahovat
    - *Obálka procesu, kterou nesmí kód překročit* -> seg. fault
  - Soubory
    - Vše je v OS chápáno jakou soubor
    - Adresáře jsou soubory, které obsahují další soubory
    - Každý soubor, adresář v procesu (při běheu) definovány souborovým deskriptorem
      - Do systému se jinak než deskriptorem nelze dostat
      - Nejsou přenositelné mezi procesy, každý proces si generuje dle svého deskriptoru
    - Souborový systém
      - Struktura je stom 
    - Dělíme na dvě skupiny
      - Znakové
      - Blokové
      d - directory
        - x - procházetelný adresář
        - x - spustitelný soubor
      c - znakové zařízení, proudy dat, nelze se vracet zpátky
      b - blokové zařízení, má svou formu a lze se pohybovat
      s - socket
      p - roura
  - Shell
    - Interaktivní program, který přijímá příkazy a předává je OS
  - MAN (manuálové stránky)
    - Systém, kterým se budeme dostávat k manuálovým stránkám
    - Ty jsou rozděleny do několika sekcí
      - 1 - Základní příkazy/programy
        - Základní příkazy, které jsou součástí OS
      - 2 - Systémové volání (napr open, read, write, close)
        - Volání systému, která nezávisí na programovacím jazyku
        - Žádná knihovna to nedokáže obejít
      - 3 - Knihovny
        - Knihovny, které jsou připojeny k programovacímu jazyku
        - Vícestavová návratová hodnota, jejíž return value nelze ošetřit jedním ifem

### Přednáška 2
- Monolitické systémy (zjistit)
- Mikrokernely (zjistit)
#### Procesy a vlákna
  -Procesy
    - Prgram x process
      - Program je hrstka insturkcí
      - Proces je spuštěný program
    - Timesharing
      - Kdyz proces ceka na jakekoliv data, tak muze preskocit a zpracovavat procesy v mezicase nekde jinde