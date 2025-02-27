# Lectures
## 1 
- Utoky na bezdratove site
  - WEP
    - Uz se skoro nepouziva
    - RC4 sifra
      - pomoci seedu generuje nahodnoud sekvenci (keystream) z WEP klice a IV (Initialization vector)
      - Initialization vektor se postupne meni a tim zarucuje originalni keystream
  - WEP64 Cracking
    - Pokud jsme schopni nachytat dosttecne mnozstvi IV packetu a provest na nich krypto analyzu, coz prolomi WEP Key 
    - Staci pasivne sedet a poslouchat (zachytit velke mnozsti packetu) a air-crack to desifruje
    - Prolomeni vznika na zakladne kolidujicich packetu
  - WPA
    - Ma slabinu behem overovani klienta v pristupovem bode
    - Klient provadi handshake behem pripojeni (musi dokazat ze zna sifrovaci klic)
    - Cracking
      - Klient zkousi ruzna hesla ze slovniku
  
  - Online cracking vlan0
    -

## 2
- nmap, netcat/nc, openssl, socat