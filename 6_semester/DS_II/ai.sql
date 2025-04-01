
CREATE OR REPLACE PROCEDURE PBackupPoslanec(p_idOrgan INTEGER)
IS
    v_backupTableName VARCHAR(50);
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_backupExistsException EXCEPTION;
BEGIN

    v_backupTableName := 'OSOBA_BACKUP_' || p_idOrgan;
     
    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = v_backupTableName;
    
    IF v_tableCount > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Záloha již existuje!');
        RAISE v_backupExistsException;
    END IF;

    v_createTable := 'create table ' || v_backupTableName || ' (
        id_osoba INT NOT NULL,
        pred VARCHAR(30) NULL,
        prijmeni VARCHAR(100) NULL,
        jmeno VARCHAR(100) NULL,
        za VARCHAR(255) NULL,
        narozeni DATE NULL,
        pohlavi CHAR(2) NULL,
        zmena DATE NULL,
        umrti DATE NULL,
        CONSTRAINT osoba' || p_idOrgan || '_pk PRIMARY KEY (id_osoba)
    )';
    
    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO ' || v_backupTableName || ' SELECT o.* FROM OSOBA o 
        INNER JOIN POSLANEC p 
            ON o.ID_OSOBA=p.ID_OSOBA
        WHERE p.ID_ORGAN=:1' USING p_idOrgan;

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_backupTableName INTO v_tableCount;

    DBMS_OUTPUT.PUT_LINE('Počet zálohovaných osob: ' || v_tableCount);
    
END;



























CREATE OR REPLACE TRIGGER THlasovaniPoslanec AFTER INSERT ON HLASOVANI_POSLANEC FOR EACH ROW
DECLARE
    v_datumHlasovani HLASOVANI.DATUM%TYPE;
    v_pocetOmluv INTEGER;
    v_osoba OSOBA%ROWTYPE;
    v_omluvenException EXCEPTION;
BEGIN
    
    IF :new.VYSLEDEK <> 'M' THEN
        SELECT DATUM INTO v_datumHlasovani FROM HLASOVANI WHERE ID_HLASOVANI = :new.ID_HLASOVANI;

        SELECT COUNT(*) INTO v_pocetOmluv FROM OMLUVA WHERE ID_POSLANEC = :new.ID_POSLANEC AND DEN = v_datumHlasovani;

        IF v_pocetOmluv > 0 THEN
            INSERT INTO ZMATECNE (ID_HLASOVANI) VALUES (:new.ID_HLASOVANI);
            UPDATE HLASOVANI SET VYSLEDEK='X' WHERE ID_HLASOVANI = :new.ID_HLASOVANI;

            SELECT o.* INTO v_osoba FROM OSOBA o INNER JOIN POSLANEC p ON p.ID_OSOBA=o.ID_OSOBA WHERE p.ID_POSLANEC = :new.ID_POSLANEC;

            DBMS_OUTPUT.PUT_LINE('Poslanec hlasoval ale přitom byl omluven!');
            DBMS_OUTPUT.PUT_LINE(v_osoba.JMENO || ' ' || v_osoba.PRIJMENI || ' - ' || TO_CHAR(v_osoba.NAROZENI));

            RAISE v_omluvenException;

        END IF;
    END IF;
    
    DBMS_OUTPUT.PUT_LINE('Hlasování bylo úspěšné.');

EXCEPTION
    WHEN v_omluvenException THEN
        DBMS_OUTPUT.PUT_LINE('Hlasování bylo označeno jako zmatečné.');
END;













































CREATE OR REPLACE PROCEDURE PBackupZarazeni(p_idPoslanec INTEGER)
IS
    v_osoba OSOBA%ROWTYPE;
    v_backupTableName VARCHAR(50);
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_backupExistsException EXCEPTION;
BEGIN

    SELECT o.* INTO v_osoba FROM POSLANEC p INNER JOIN OSOBA o ON o.ID_OSOBA=p.ID_OSOBA WHERE p.ID_POSLANEC = p_idPoslanec;

    DBMS_OUTPUT.PUT_LINE('Osoba:' || v_osoba.JMENO || ' ' || v_osoba.PRIJMENI);

    v_backupTableName := 'ZARAZENI_BACKUP_' || p_idPoslanec;
     
    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = v_backupTableName;
    
    IF v_tableCount > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Záloha již existuje!');
        RAISE v_backupExistsException;
    END IF;

    v_createTable := 'create table ' || v_backupTableName || ' (
        id_osoba INT NULL,
        id_of INT NULL,
        cl_funkce INT NULL,
        od_o DATE NULL,
        do_o DATE NULL,
        od_f DATE NULL,
        do_f DATE NULL,
        CONSTRAINT zarazeni_fk_id_osoba' || p_idPoslanec || ' FOREIGN KEY (id_osoba) REFERENCES osoba (id_osoba)
    )';

    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO ' || v_backupTableName || ' SELECT z.* FROM ZARAZENI z WHERE z.ID_OSOBA = :1' USING v_osoba.ID_OSOBA;

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_backupTableName INTO v_tableCount;

    DBMS_OUTPUT.PUT_LINE('Počet zálohovaných zařazení: ' || v_tableCount);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Záloha selhala, poslanec neexistuje.');
END;






































CREATE OR REPLACE TRIGGER TOmluvaPoslanec AFTER INSERT ON OMLUVA FOR EACH ROW
DECLARE
    v_pocetHlasovani INTEGER;
    v_pocetVsechHlasovani INTEGER;
    v_osoba OSOBA%ROWTYPE;
BEGIN
    v_pocetHlasovani := 0;
    v_pocetVsechHlasovani := 0;

    SELECT o.* INTO v_osoba FROM OSOBA o INNER JOIN POSLANEC p ON o.ID_OSOBA=p.ID_OSOBA WHERE p.ID_POSLANEC = :new.ID_POSLANEC;

    DBMS_OUTPUT.PUT_LINE('Poslanec: ' || v_osoba.JMENO || ' ' || v_osoba.PRIJMENI);

    FOR v_hlasovani IN (
        SELECT h.* FROM HLASOVANI h
            INNER JOIN HLASOVANI_POSLANEC hp 
                ON h.ID_HLASOVANI=hp.ID_HLASOVANI
            WHERE hp.ID_POSLANEC = :new.ID_POSLANEC AND h.ID_ORGAN = :new.ID_ORGAN AND h.DATUM = :new.DEN
    ) LOOP
        v_pocetVsechHlasovani := v_pocetVsechHlasovani + 1;
        
        IF v_hlasovani.VYSLEDEK <> 'X' THEN
            INSERT INTO ZMATECNE (ID_HLASOVANI) VALUES (v_hlasovani.ID_HLASOVANI);
            UPDATE HLASOVANI SET VYSLEDEK='X' WHERE ID_HLASOVANI = v_hlasovani.ID_HLASOVANI;

            DBMS_OUTPUT.PUT_LINE('Hlasování bylo označeno jako zmatečné.');
            DBMS_OUTPUT.PUT_LINE(v_hlasovani.ID_HLASOVANI || ' - PRO: ' || v_hlasovani.PRO || '; PROTI: ' || v_hlasovani.PROTI || '; VYSLEDEK: ' || v_hlasovani.VYSLEDEK);

            v_pocetHlasovani := v_pocetHlasovani + 1;
        END IF;
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Počet problematických hlasování: ' || v_pocetHlasovani || ' z ' || v_pocetVsechHlasovani);

END;



















CREATE OR REPLACE FUNCTION FStatistika(p_idOsoby INTEGER, p_aggFn VARCHAR) RETURN FLOAT
AS 
    v_aggregationResult FLOAT;
    v_jmeno OSOBA.JMENO%TYPE;
    v_prijmeni OSOBA.PRIJMENI%TYPE;
    v_idPoslanec POSLANEC.ID_POSLANEC%TYPE;
    v_notPoslanecException EXCEPTION;
    v_ivalidAggFunctionException EXCEPTION;
BEGIN

    IF p_aggFn <> 'AVG' AND p_aggFn <> 'MAX' AND p_aggFn <> 'MIN' THEN
        DBMS_OUTPUT.PUT_LINE('Funkci ' || p_aggFn || ' nelze použít.');
        RAISE v_ivalidAggFunctionException;
    END IF;

    SELECT o.JMENO, o.PRIJMENI, p.ID_POSLANEC INTO v_jmeno, v_prijmeni, v_idPoslanec FROM OSOBA o 
        LEFT JOIN POSLANEC p 
            ON o.ID_OSOBA=p.ID_OSOBA
        WHERE o.ID_OSOBA=p_idOsoby;

    IF v_idPoslanec IS NULL THEN
        RAISE v_notPoslanecException;
    END IF;

    EXECUTE IMMEDIATE 'SELECT ROUND(' || p_aggFn || '(CAST(s.DO_SCHUZE AS DATE) - CAST(s.OD_SCHUZE AS DATE)) * 24, 1) FROM SCHUZE s 
        INNER JOIN POSLANEC p 
            ON s.ID_ORGAN=p.ID_ORGAN
        INNER JOIN OSOBA o 
            ON o.ID_OSOBA=p.ID_OSOBA
        WHERE o.ID_OSOBA=:1' INTO v_aggregationResult USING p_idOsoby;
    

    DBMS_OUTPUT.PUT_LINE(v_jmeno || ' ' || v_prijmeni);
    DBMS_OUTPUT.PUT_LINE('Výsledek (' || p_aggFn || '): ' || TO_CHAR(v_aggregationResult) || ' hodin.');

    RETURN v_aggregationResult;
EXCEPTION 
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Osoba nebyla nalezena.');
        RETURN NULL;
    WHEN v_notPoslanecException THEN
        DBMS_OUTPUT.PUT_LINE('Není poslanec.');
        RETURN NULL;
END;





















CREATE OR REPLACE TRIGGER THlasovani AFTER INSERT ON HLASOVANI_POSLANEC FOR EACH ROW
DECLARE
    v_hlasovani HLASOVANI%ROWTYPE;
    v_vysledek HLASOVANI.VYSLEDEK%TYPE;
    v_kvorum HLASOVANI.KVORUM%TYPE;
BEGIN

    
    SELECT * INTO v_hlasovani FROM HLASOVANI WHERE ID_HLASOVANI = :new.ID_HLASOVANI;
    DBMS_OUTPUT.PUT_LINE('Starý stav hlasování');
    DBMS_OUTPUT.PUT_LINE(v_hlasovani.PRO || ' vs ' || v_hlasovani.PROTI || ' |' || v_hlasovani.KVORUM || ' => ' || v_hlasovani.VYSLEDEK);

    IF :new.VYSLEDEK = 'A' THEN
        UPDATE HLASOVANI SET PRIHLASENO = PRIHLASENO + 1, PRO = PRO + 1  WHERE ID_HLASOVANI=:new.ID_HLASOVANI;
    ELSIF :new.VYSLEDEK = 'B' OR :new.VYSLEDEK = 'N' THEN
        UPDATE HLASOVANI SET PRIHLASENO = PRIHLASENO + 1, PROTI = PROTI + 1  WHERE ID_HLASOVANI=:new.ID_HLASOVANI;
    ELSIF :new.VYSLEDEK = 'C' OR :new.VYSLEDEK = 'K' THEN
        UPDATE HLASOVANI SET PRIHLASENO = PRIHLASENO + 1, ZDRZEL = ZDRZEL + 1  WHERE ID_HLASOVANI=:new.ID_HLASOVANI;
    ELSIF :new.VYSLEDEK = 'F' OR :new.VYSLEDEK = '@' THEN
        UPDATE HLASOVANI SET PRIHLASENO = PRIHLASENO + 1, NEHLASOVAL = NEHLASOVAL + 1  WHERE ID_HLASOVANI=:new.ID_HLASOVANI;
    END IF;

    SELECT * INTO v_hlasovani FROM HLASOVANI WHERE ID_HLASOVANI=:new.ID_HLASOVANI;

    v_kvorum := FLOOR(v_hlasovani.PRIHLASENO / 2) + 1;

    IF v_hlasovani.PRO >= v_kvorum THEN
        v_vysledek := 'A';
    ELSE
        v_vysledek := 'R';
    END IF;

    UPDATE HLASOVANI SET KVORUM=v_kvorum, VYSLEDEK=v_vysledek WHERE ID_HLASOVANI = :new.ID_HLASOVANI;

    SELECT * INTO v_hlasovani FROM HLASOVANI WHERE ID_HLASOVANI=:new.ID_HLASOVANI;
    DBMS_OUTPUT.PUT_LINE('Nový stav hlasování');
    DBMS_OUTPUT.PUT_LINE(v_hlasovani.PRO || ' vs ' || v_hlasovani.PROTI || ' |' || v_hlasovani.KVORUM || ' => ' || v_hlasovani.VYSLEDEK);


END;






















CREATE OR REPLACE FUNCTION FStatistika(p_idPoslanec INTEGER, p_sloupec VARCHAR) RETURN FLOAT
AS 
    v_aggregationResult FLOAT;
    v_jmeno OSOBA.JMENO%TYPE;
    v_prijmeni OSOBA.PRIJMENI%TYPE;
    v_invalidColumnNameException EXCEPTION;
BEGIN

    IF p_sloupec <> 'PRO' AND p_sloupec <> 'PROTI' AND p_sloupec <> 'ZDRZEL' THEN
        DBMS_OUTPUT.PUT_LINE('Sloupec ' || p_sloupec || ' nelze použít.');
        RAISE v_invalidColumnNameException;
    END IF;

    SELECT o.JMENO, o.PRIJMENI INTO v_jmeno, v_prijmeni FROM OSOBA o 
        LEFT JOIN POSLANEC p 
            ON o.ID_OSOBA=p.ID_OSOBA
        WHERE p.ID_POSLANEC=p_idPoslanec;


    EXECUTE IMMEDIATE 'SELECT AVG(' || p_sloupec || ') FROM HLASOVANI h INNER JOIN HLASOVANI_POSLANEC hp ON hp.ID_HLASOVANI=h.ID_HLASOVANI WHERE hp.ID_POSLANEC = :1' INTO v_aggregationResult USING p_idPoslanec;
    
    DBMS_OUTPUT.PUT_LINE(v_jmeno || ' ' || v_prijmeni);
    DBMS_OUTPUT.PUT_LINE('Průměr (' || p_sloupec || ') pro všechna hlasování, kterých se účastnil: ' || TO_CHAR(v_aggregationResult));

    RETURN v_aggregationResult;
EXCEPTION 
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Poslanec nenalazen.');
        RETURN NULL;
END;





















CREATE OR REPLACE FUNCTION FGetPotentialVoteOutcome(f_idPoslanec INTEGER, f_idHlasovani INTEGER, f_vysledek HLASOVANI.VYSLEDEK%TYPE) RETURN HLASOVANI.VYSLEDEK%TYPE
IS
    v_hlasovani HLASOVANI%ROWTYPE;
    v_vysledek HLASOVANI.VYSLEDEK%TYPE;
    v_kvorum HLASOVANI.KVORUM%TYPE;
    v_hlasuPoslance INTEGER;
    v_alreadyVotedException EXCEPTION;
BEGIN

    SELECT * INTO v_hlasovani FROM HLASOVANI WHERE ID_HLASOVANI = f_idHlasovani;

    SELECT COUNT(*) INTO v_hlasuPoslance FROM HLASOVANI_POSLANEC WHERE ID_HLASOVANI = f_idHlasovani AND ID_POSLANEC = f_idPoslanec;

    IF v_hlasuPoslance > 0 THEN
        RAISE v_alreadyVotedException;
    END IF;

    DBMS_OUTPUT.PUT_LINE('Starý stav hlasování');
    DBMS_OUTPUT.PUT_LINE(v_hlasovani.PRO || ' vs ' || v_hlasovani.PROTI || '; kvorum = ' || v_hlasovani.KVORUM || '; vysledek = ' || v_hlasovani.VYSLEDEK);

    IF f_vysledek = 'A' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.PRO := v_hlasovani.PRO + 1;
    ELSIF f_vysledek = 'B' OR f_vysledek = 'N' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.PROTI := v_hlasovani.PROTI + 1;
    ELSIF f_vysledek = 'C' OR f_vysledek = 'K' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.ZDRZEL := v_hlasovani.ZDRZEL + 1;
    ELSIF f_vysledek = 'F' OR f_vysledek = '@' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.NEHLASOVAL := v_hlasovani.NEHLASOVAL + 1;
    END IF;

    v_kvorum := FLOOR(v_hlasovani.PRIHLASENO / 2) + 1;

    IF v_hlasovani.PRO >= v_kvorum THEN
        v_vysledek := 'A';
    ELSE
        v_vysledek := 'R';
    END IF;

    DBMS_OUTPUT.PUT_LINE('Nový stav hlasování');
    DBMS_OUTPUT.PUT_LINE(v_hlasovani.PRO || ' vs ' || v_hlasovani.PROTI || '; kvorum = ' || v_hlasovani.KVORUM || '; vysledek = ' || v_vysledek);

    RETURN v_vysledek;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RETURN NULL;
END;

















/* A1
Vytvořte v tabulce poslanec atribut absence_level typu char(1) s možnými hodnotami 'L', 'M', 'H'. Následně napište proceduru SetAbsenceLevel, kde na vstupu budou parametry od a do. 
Procedura každému poslanci spočítá počet absencí za období definované parametry. Pokud počet absencí bude < 10 dní, absence_level mu nastaví na 'L', pokud bude počet absencí v rozsahu 11-20 dní, 
absence_level mu nastaví na 'M'. Při větším počtu absencí mu nastaví absence_level na 'H'. Za jednu absenci považujte jeden záznam v tabulce omluva, přičemž den absence je definován ve sloupci den. Procedura bude řešena jako transakce. */

ALTER TABLE poslanec
ADD absence_level CHAR(1) CHECK (absence_level IN ('L', 'M', 'H'));

CREATE OR REPLACE PROCEDURE SetAbsenceLevel(p_od DATE, p_do DATE) IS
BEGIN
    FOR rec IN (
                SELECT poslanec.id_poslanec, COUNT(omluva.id_poslanec) AS pocet_absenci
                FROM poslanec left join omluva on poslanec.id_poslanec = omluva.id_poslanec
                AND den BETWEEN p_od AND p_do
                GROUP BY poslanec.id_poslanec) LOOP
        UPDATE poslanec
        SET absence_level =
            CASE
                WHEN rec.pocet_absenci < 10 THEN 'L'
                WHEN rec.pocet_absenci BETWEEN 11 AND 20 THEN 'M'
                ELSE 'H'
            END
        WHERE id_poslanec = rec.id_poslanec;
    END LOOP;
    COMMIT;
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
END;

/* A2
Napište funkci, která bude vkládat záznam do tabulky zmatecne_hlasovani_poslanec a bude obsahovat parametry id_hlasovani, id_osoba a rok. Procedura nejprve zkontroluje, zda osoba s daným id existuje, 
a pokud neexistuje, vypíše na obrazovku, že neexistuje, a procedura se ukončí. Poté zkontroluje, zda hlasování s daným id existuje, a pokud neexistuje, vypíše na obrazovku, že neexistuje, 
a procedura se ukončí. Pokud osoba i hlasování existují, procedura spočítá, kolik zmatených hlasování daná osoba v daném roce měla. Pokud méně než 10, mód se nastaví na 0, pokud více než 10, 
mód se nastaví na 1. Nakonec záznam vloží do tabulky, vypíše na obrazovku "Zmatené hlasování zaevidováno" a vrátí počet zmatených hlasování v daném roce. Funkce bude řešena jako transakce. */

CREATE OR REPLACE FUNCTION InsertConfusedVote(p_id_hlasovani IN NUMBER, p_id_osoba IN NUMBER, p_rok NUMBER) RETURN NUMBER IS
    pocet_zmatenych_hlasovani int;
    pocet_hlasovani int;
    pocet_osob int;
BEGIN
    SELECT COUNT(*) INTO pocet_osob
    FROM osoba
    WHERE id_osoba = p_id_osoba;

    IF pocet_osob = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Osoba s daným ID neexistuje.');
        RETURN -1;
    END IF;

    -- Kontrola existence hlasování
    SELECT COUNT(*) into pocet_hlasovani
    FROM hlasovani
    WHERE id_hlasovani = p_id_hlasovani;

    IF pocet_hlasovani = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Hlasování s daným ID neexistuje.');
        RETURN -1;
    END IF;

    -- Spočítání zmatených hlasování dané osoby v daném roce
    SELECT COUNT(*)
    INTO pocet_zmatenych_hlasovani
    FROM zmatecne_hlasovani_poslanec join hlasovani on zmatecne_hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani
    WHERE id_osoba = p_id_osoba  AND EXTRACT(YEAR FROM datum) = p_rok;

    -- Nastavení módu
    IF pocet_zmatenych_hlasovani <= 5 THEN
        INSERT INTO zmatecne_hlasovani_poslanec VALUES (p_id_hlasovani, p_id_osoba, 0);
    ELSE
        INSERT INTO zmatecne_hlasovani_poslanec VALUES (p_id_hlasovani, p_id_osoba, 1);
    END IF;

    DBMS_OUTPUT.PUT_LINE('Zmatené hlasování zaevidováno.');
    COMMIT;
    RETURN pocet_zmatenych_hlasovani;
EXCEPTION
   WHEN OTHERS THEN
      ROLLBACK;
END;

/* B1
Vytvořte v tabulce schuze atribut vote_level typu char(1) s možnými hodnotami 'L', 'M', 'H'. Následně napište proceduru SetVoteLevel, kde na vstupu budou parametry od a do. Procedura 
pro každou schůzi spočítá počet hlasování, které se v ní uskutečnilo, za období definované parametry. Pokud počet hlasování bude < 10, vote_level mu nastaví na 'L', pokud bude počet 
hlasování v rozsahu 11-20, vote_level mu nastaví na 'M'. Při větším počtu hlasování mu nastaví vote_level na 'H'. Procedura bude řešena jako transakce. */

ALTER TABLE schuze
ADD vote_level char(1) CHECK (vote_level IN ('L', 'M', 'H'));

CREATE OR REPLACE PROCEDURE SetVoteLevel(p_od DATE, p_do DATE) IS
BEGIN
    FOR rec IN (SELECT schuze.schuze, COUNT(hlasovani.schuze) AS pocet_hlasovani
                FROM schuze left join hlasovani on schuze.schuze = hlasovani.schuze
                WHERE datum BETWEEN p_od AND p_do
                GROUP BY schuze.schuze) LOOP
        UPDATE schuze
        SET vote_level =
            CASE
                WHEN rec.pocet_hlasovani < 100 THEN 'L'
                WHEN rec.pocet_hlasovani BETWEEN 101 AND 1000 THEN 'M'
                ELSE 'H'
            END
        WHERE schuze = rec.schuze;
    END LOOP;
    COMMIT;
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
END;

/* B2
Napište trigger, který bude spuštěn před vložením záznamu do tabulky bod_schuze. Spouštěč zkontroluje, zda bod schůze nevkladame do schůze, která již skončila nebo nezačala (tj. aktuální 
datum nespadá do intervalu od_schuze-do schuze) nebo se netýká orgánu, kterému již skončilo působení (tj. aktuální datum nespadá do intervalu od_organ-do_organ). Pokud tyto podmínky splňuje, 
trigger nastaví atribut bod na aktuální počet bodů v dané schůzi + 1. Následně zkontroluje, zda byl vyplněn úplný název, a pokud název nebyl vyplněn, nebo jde o první bod schůze, 
nastaví atribut uplny_naz na 'Úvodní bod'. */

CREATE OR REPLACE TRIGGER before_insert_bod_schuze
BEFORE INSERT ON bod_schuze
FOR EACH ROW
DECLARE
    aktualni_schuze_skoncila EXCEPTION;
    organ_jiz_skoncil EXCEPTION;
    v_od_schuze date;
    v_do_schuze date;
    v_od_organ date;
    v_do_organ date;
BEGIN
   select od_schuze, do_schuze into v_od_schuze, v_do_schuze 
   from schuze 
   where id_schuze = :NEW.id_schuze;
   
    -- Kontrola, zda schůze již skončila nebo nezačala
    IF (v_od_schuze > CURRENT_DATE AND v_do_schuze < CURRENT_DATE) THEN
        RAISE aktualni_schuze_skoncila;
    END IF;

   select od_organ, do_organ into v_od_organ, v_do_organ 
   from organ join schuze on organ.id_organ = schuze.id_organ 
   where id_schuze = :NEW.id_schuze;
   
    -- Kontrola, zda se bod týká orgánu, který již skončil působení
    IF (v_od_organ > CURRENT_DATE AND v_do_organ < CURRENT_DATE) THEN
        RAISE organ_jiz_skoncil;
    END IF;

    -- Nastavení atributu bod na aktuální počet bodů v dané schůzi + 1
    SELECT COUNT(*) + 1
    INTO :NEW.bod
    FROM bod_schuze
    WHERE id_schuze = :NEW.id_schuze;

    -- Kontrola, zda byl vyplněn úplný název
    IF :NEW.uplny_naz IS NULL OR :NEW.bod = 1 THEN
        :NEW.uplny_naz := 'Úvodní bod';
    END IF;
END;






























CREATE OR REPLACE PROCEDURE POpravZarazeni(p_fromDate DATE, p_untilDate DATE)
IS
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_zarazeni INTEGER;
BEGIN

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = 'ZARAZENI_FIXED';
    
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table Zarazeni_fixed';
    END IF;

    v_createTable := 'create table Zarazeni_fixed (
        id_osoba INT NULL,
        id_organ INT NULL,
        id_funkce INT NULL,
        od_o DATE NULL,
        do_o DATE NULL,
        od_f DATE NULL,
        do_f DATE NULL,
        CONSTRAINT zarazeni_fixed_fk_id_osoba FOREIGN KEY (id_osoba) REFERENCES osoba (id_osoba),
        CONSTRAINT zarazeni_fixed_fk_id_organ FOREIGN KEY (id_organ) REFERENCES organ (id_organ),
        CONSTRAINT zarazeni_fixed_fk_id_funkce FOREIGN KEY (id_funkce) REFERENCES funkce (id_funkce)
    )';


    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO Zarazeni_fixed SELECT id_osoba, id_of, null, od_o, do_o, od_f, do_f FROM Zarazeni where cl_funkce=0';
    EXECUTE IMMEDIATE 'INSERT INTO Zarazeni_fixed SELECT id_osoba, null, id_of, od_o, do_o, od_f, do_f FROM Zarazeni where cl_funkce=1';
    
    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM Zarazeni_fixed WHERE id_organ is not null and OD_O > :1 AND DO_O < :2' INTO v_zarazeni USING p_fromDate, p_untilDate;
    
    DBMS_OUTPUT.PUT_LINE('Počet zařazení do orgánů v době od ' || p_fromDate || ' do ' || p_untilDate || ': ' || v_zarazeni);

END;




















CREATE OR REPLACE TRIGGER TUmrti BEFORE UPDATE ON Osoba FOR EACH ROW
DECLARE
    v_hlasovaniCount INTEGER;
    v_idPoslanec INTEGER;
    v_invalidUmrtiException EXCEPTION;
BEGIN

    IF :new.umrti IS NOT NULL THEN

        SELECT COUNT(*) INTO v_hlasovaniCount FROM Hlasovani h
            INNER JOIN Hlasovani_poslanec hp 
                ON h.id_hlasovani = hp.id_hlasovani 
            INNER JOIN Poslanec p 
                ON p.id_poslanec = hp.id_poslanec 
            WHERE p.id_osoba = :new.id_osoba AND h.datum > :new.umrti;

        IF v_hlasovaniCount > 0 THEN
            DBMS_OUTPUT.PUT_LINE('Špatné datum úmrtí -> poslanec nemohl hlasovat po smrti.');
            RAISE v_invalidUmrtiException;
        END IF;

        DELETE FROM Omluva WHERE OD > :new.umrti AND id_poslanec IN (SELECT id_poslanec FROM Poslanec WHERE id_osoba = :new.id_osoba);
        
        DBMS_OUTPUT.PUT_LINE('Počet odstraněných řádků:' || SQL%ROWCOUNT); -- případně select počtu před delete

    END IF;

END;



























CREATE OR REPLACE PROCEDURE POpravOmluva
IS
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_zarazeni INTEGER;
BEGIN

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = 'OMLUVA_FIXED';
    
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table Omluva_fixed';
    END IF;

    v_createTable := 'create table Omluva_fixed (
    id_organ INT NOT NULL,
    id_poslanec INT NOT NULL,
    od TIMESTAMP NULL,
    do TIMESTAMP NULL,
    CONSTRAINT omluva_fixed_fk_id_organ FOREIGN KEY (id_organ) REFERENCES organ (id_organ),
    CONSTRAINT omluva_fixed_fk_id_poslanec FOREIGN KEY (id_poslanec) REFERENCES poslanec (id_poslanec)
    )';

    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO Omluva_fixed SELECT 
        id_organ, 
        id_poslanec,
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' 00:00:00'', ''YYYY-MM-DD HH24:MI:SS''), 
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' 23:59:59'', ''YYYY-MM-DD HH24:MI:SS'')
     FROM Omluva WHERE od IS NULL AND do IS NULL';
    
    EXECUTE IMMEDIATE 'INSERT INTO Omluva_fixed SELECT 
        id_organ, 
        id_poslanec,
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' '' || TO_CHAR(OD, ''HH24:MI:SS''), ''YYYY-MM-DD HH24:MI:SS''), 
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' '' || TO_CHAR(DO, ''HH24:MI:SS''), ''YYYY-MM-DD HH24:MI:SS'')
     FROM Omluva WHERE od IS NOT NULL AND do IS NOT NULL';

END;



















CREATE OR REPLACE FUNCTION FCheckDenUmrti(f_idOsoba INTEGER, f_datumUmrti DATE) RETURN VARCHAR 
IS
    v_osoba OSOBA%ROWTYPE;
    v_hlasovaniCount INTEGER;
    v_result VARCHAR(10000);
BEGIN
    
    SELECT * INTO v_osoba FROM Osoba WHERE id_osoba = f_idOsoba;

    v_result := v_osoba.jmeno || ' ' || v_osoba.prijmeni || CHR(10);

    IF f_datumUmrti IS NULL THEN
        v_result := v_result || 'úmrtí nelze zrušit';
        RETURN v_result;
    END IF;

    IF f_datumUmrti > CURRENT_DATE THEN
        v_result := v_result ||  'úmrtí nemůže být v budoucnu';
        RETURN v_result;
    END IF;


    IF f_datumUmrti < v_osoba.narozeni THEN
        v_result := v_result ||  'úmrtí nemůže být před narozením';
        RETURN v_result;
    END IF;


    IF v_osoba.umrti IS NOT NULL THEN
        v_result := v_result || 'již mrtvý' || f_idOsoba;
        RETURN v_result;
    END IF;

    SELECT COUNT(*) INTO v_hlasovaniCount FROM Hlasovani h
        INNER JOIN Hlasovani_poslanec hp 
             ON h.id_hlasovani = hp.id_hlasovani 
         INNER JOIN Poslanec p 
               ON p.id_poslanec = hp.id_poslanec 
         WHERE p.id_osoba = f_idOsoba AND h.datum > f_datumUmrti;

    IF v_hlasovaniCount > 0 THEN
        v_result := v_result || 'Chybné zadání. Osoba hlasovala po smrti: ' || v_hlasovaniCount || f_idOsoba;
        RETURN v_result;
    END IF;

    v_result := v_result || 'Vše v pořádku.' || f_idOsoba;
    RETURN v_result;

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RETURN 'osoba nebyla nalezena';

END;
















CREATE OR REPLACE PROCEDURE PCreateOsoba2(p_minBornDate VARCHAR, p_maxBornDate VARCHAR)
IS
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_count INTEGER;
    v_invalidRangeException EXCEPTION;
BEGIN

    IF TO_DATE(p_minBornDate, 'YYYY-MM-DD') > TO_DATE(p_maxBornDate, 'YYYY-MM-DD') THEN
        DBMS_OUTPUT.PUT_LINE('Špatné zadané časové rozmezí:' || p_minBornDate || ' - ' || p_maxBornDate);
        RAISE v_invalidRangeException;
    END IF;

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = 'OSOBA2';
    
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table OSOBA2';
    END IF;

    v_createTable := 'create table osoba2 (
        id_osoba INT NOT NULL,
        pred VARCHAR(30) NULL,
        prijmeni VARCHAR(100) NULL,
        jmeno VARCHAR(100) NULL,
        za VARCHAR(255) NULL,
        narozeni DATE NULL,
        pohlavi CHAR(2) NULL,
        zmena DATE NULL,
        umrti DATE NULL,
        CONSTRAINT osoba2_pk PRIMARY KEY (id_osoba)
    )';
    
    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO OSOBA2 SELECT * FROM osoba WHERE narozeni BETWEEN :1 AND :2' USING TO_DATE(p_minBornDate, 'YYYY-MM-DD'), TO_DATE(p_maxBornDate, 'YYYY-MM-DD');

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM OSOBA2' INTO v_count;

    DBMS_OUTPUT.PUT_LINE('Počet zkopírovaných záznamů: ' || v_count);
END;


















CREATE OR REPLACE FUNCTION FExportOmluv(f_idOsoba INTEGER, f_minDate DATE, f_maxDate DATE) RETURN VARCHAR
IS 
    v_osoba OSOBA%ROWTYPE;
    v_result VARCHAR(3000);
    v_notFoundException EXCEPTION;
BEGIN 

    SELECT * INTO v_osoba FROM OSOBA WHERE ID_OSOBA=f_idOsoba;
    
    v_result := v_osoba.JMENO || ' ' || v_osoba.PRIJMENI || CHR(10);
    IF v_osoba.POHLAVI = 'M' THEN
        v_result := v_result || 'MUŽ';
    ELSE 
        v_result := v_result || 'ŽENA';
    END IF;

    v_result := v_result || CHR(10);
    
    FOR v_omluva IN (
        SELECT DEN FROM OMLUVA o 
            INNER JOIN POSLANEC p 
                ON o.ID_POSLANEC=p.ID_POSLANEC 
            WHERE p.ID_OSOBA=f_idOsoba AND o.DEN BETWEEN f_minDate AND f_maxDate
        ) 
    LOOP
        v_result := v_result || TO_CHAR(v_omluva.DEN) || CHR(10);
    END LOOP;
    
    RETURN v_result;

EXCEPTION 
    WHEN NO_DATA_FOUND THEN
        RETURN 'NO_DATA';
END;



















CREATE OR REPLACE PROCEDURE PCreateSchuze(p_idOrgan ORGAN.ID_ORGAN%TYPE)
IS
    v_organ ORGAN%ROWTYPE;

    v_tableName VARCHAR(50);
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_count INTEGER;
BEGIN

    SELECT * INTO v_organ FROM ORGAN WHERE ID_ORGAN = p_idOrgan;

    DBMS_OUTPUT.PUT_LINE('Orgán:' || v_organ.nazev_organu_cz || ' (' || v_organ.ZKRATKA || ')');

    v_tableName := 'SCHUZE_' || TO_CHAR(p_idOrgan);

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = v_tableName;
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table ' || v_tableName;
    END IF;

    v_createTable := 'create table ' || v_tableName || ' (
        id_schuze INT NOT NULL,
        id_organ INT NULL,
        schuze INT NULL,
        od_schuze TIMESTAMP NULL,
        do_schuze TIMESTAMP NULL,
        aktualizace TIMESTAMP NULL,
        CONSTRAINT schuze' || TO_CHAR(p_idOrgan) || '_pk PRIMARY KEY (id_schuze),
        CONSTRAINT schuze' || TO_CHAR(p_idOrgan) || '_uniq UNIQUE(id_organ, schuze),
        CONSTRAINT schuze' || TO_CHAR(p_idOrgan) || '_fk_id_organ FOREIGN KEY (id_organ) REFERENCES organ (id_organ)
    )';

    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO ' || v_tableName || ' SELECT * FROM SCHUZE WHERE ID_ORGAN = :1' USING p_idOrgan;

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_tableName INTO v_count;

    DBMS_OUTPUT.PUT_LINE('Počet zkopírovaných záznamů: ' || v_count);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Orgán nenalezen.');
END;





















CREATE OR REPLACE FUNCTION FExportHlasovani(f_idHlasovani HLASOVANI.ID_HLASOVANI%TYPE) RETURN VARCHAR
IS 
    v_nazev BOD_SCHUZE.UPLNY_NAZ%TYPE;
    v_datum HLASOVANI.DATUM%TYPE;

    v_result VARCHAR(32767);
    v_notFoundException EXCEPTION;
BEGIN 

    SELECT o.NAZEV_ORGANU_CZ, h.DATUM INTO v_nazev, v_datum FROM HLASOVANI h
        INNER JOIN ORGAN o
            ON o.ID_ORGAN = h.ID_ORGAN
        WHERE h.ID_HLASOVANI = f_idHlasovani;

    v_result := v_nazev || ' (' || v_datum || ')' || CHR(10);

    FOR v_hlas IN (
        SELECT hp.VYSLEDEK, o.JMENO, o.PRIJMENI FROM HLASOVANI_POSLANEC hp 
            INNER JOIN POSLANEC p 
                ON hp.ID_POSLANEC=p.ID_POSLANEC 
            INNER JOIN OSOBA o 
                ON o.ID_OSOBA=p.ID_OSOBA 
            WHERE hp.ID_HLASOVANI=f_idHlasovani AND hp.VYSLEDEK <> '@'
        ) 
    LOOP
        v_result := v_result || v_hlas.JMENO || ' ' || v_hlas.PRIJMENI || ': ' || v_hlas.VYSLEDEK || CHR(10);
    END LOOP;
    
    RETURN v_result;

EXCEPTION 
    WHEN NO_DATA_FOUND THEN
        RETURN 'NO_DATA';
END;






















CREATE OR REPLACE PROCEDURE PSplitVotes (p_fromYear INTEGER, p_untilYear INTEGER)
AS
    v_tableName VARCHAR(500);
    v_recordCount INTEGER;
    v_invalidRangeException EXCEPTION;
BEGIN

    IF p_fromYear > p_untilYear THEN
        DBMS_OUTPUT.PUT_LINE('Chybně zadaný interval: ' || p_fromYear || ' - ' || p_untilYear);
        RAISE v_invalidRangeException;
    END IF;
    
    FOR v_table IN (
        SELECT * FROM user_tables WHERE TABLE_NAME LIKE 'HLASOVANI_ROK_%'
    ) LOOP
        EXECUTE IMMEDIATE 'DROP TABLE ' || v_table.TABLE_NAME;
    END LOOP;

    FOR v_year IN  (
        SELECT DISTINCT EXTRACT(YEAR FROM datum) YEAR FROM hlasovani WHERE EXTRACT(YEAR FROM datum) >= p_fromYear AND EXTRACT(YEAR FROM datum) <= p_untilYear
    ) LOOP
        v_tableName := 'HLASOVANI_ROK_' ||  TO_CHAR(v_year.YEAR);

        EXECUTE IMMEDIATE 'CREATE TABLE ' ||  v_tableName || ' (datum DATE, pro INTEGER, proti INTEGER)';

        EXECUTE IMMEDIATE 'INSERT INTO ' ||  v_tableName || ' (datum, pro, proti) SELECT datum, pro, proti FROM hlasovani WHERE EXTRACT(YEAR FROM datum)=:1' USING v_year.year;

        EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_tableName INTO v_recordCount;

        DBMS_OUTPUT.PUT_LINE(v_tableName || ': ' || v_recordCount || ' zaznamů');
    END LOOP;

END;



















-- drop table TOO_MANY_ABSENCE_LOG;

CREATE TABLE TOO_MANY_ABSENCE_LOG (
    ID_POSLANEC INTEGER, 
    DEN_OMLUVY DATE, 
    DATUM_PRIDANI TIMESTAMP
);

CREATE OR REPLACE TRIGGER TPreventTooManyAbsence BEFORE INSERT ON OMLUVA FOR EACH ROW
DECLARE
    v_date DATE;
    v_numberOfExcuse INTEGER;
    v_numberOfExcusePerDay INTEGER;
    v_notAllowedException EXCEPTION;
BEGIN
    
    SELECT COUNT(*) INTO v_numberOfExcusePerDay FROM OMLUVA WHERE den=:new.den AND ID_POSLANEC = :new.ID_POSLANEC;

    IF v_numberOfExcusePerDay > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Duplicita');
        RAISE_APPLICATION_ERROR(-1001, 'duplicitni omluva');
    END IF;

    
    SELECT COUNT(*) INTO v_numberOfExcuse
    FROM OMLUVA
    WHERE den BETWEEN ADD_MONTHS(:new.den, -1) AND ADD_MONTHS(:new.den, 1) AND ID_POSLANEC = :new.ID_POSLANEC;

    DBMS_OUTPUT.PUT_LINE('Počet omluv:' || v_numberOfExcuse);

    IF v_numberOfExcuse >= 10 THEN
        INSERT INTO TOO_MANY_ABSENCE_LOG (ID_POSLANEC, DATUM_PRIDANI, DEN_OMLUVY)
        VALUES (:new.ID_POSLANEC, CURRENT_TIMESTAMP, :new.den);

        DBMS_OUTPUT.PUT_LINE('Příliš mnoho omluv (' || v_numberOfExcuse || ').');
    END IF;

END;

















CREATE OR REPLACE PROCEDURE PSplitOsoba (p_fromDate DATE, p_untilDate DATE)
AS
    v_tableName VARCHAR(500);
    v_recordCount INTEGER;
    v_invalidRangeException EXCEPTION;
BEGIN

    IF p_fromDate > p_untilDate THEN
        DBMS_OUTPUT.PUT_LINE('Chybně zadaný interval: ' || TO_CHAR(p_fromDate) || ' - ' || TO_CHAR(p_untilDate));
        RAISE v_invalidRangeException;
    END IF;

    UPDATE OSOBA SET POHLAVI='Z' WHERE POHLAVI='Ž';
    
    FOR v_table IN (
        SELECT * FROM user_tables WHERE TABLE_NAME LIKE 'OSOBA_%'
    ) LOOP
        EXECUTE IMMEDIATE 'DROP TABLE ' || v_table.TABLE_NAME;
    END LOOP;

    FOR v_pohlavi IN  (
        SELECT DISTINCT POHLAVI FROM OSOBA WHERE NAROZENI BETWEEN p_fromDate AND p_untilDate
    ) LOOP
        v_tableName := 'OSOBA_' ||  v_pohlavi.POHLAVI;

        EXECUTE IMMEDIATE 'CREATE TABLE ' ||  v_tableName || ' (jmeno VARCHAR2(100), prijmeni VARCHAR2(100), narozeni DATE)';

        EXECUTE IMMEDIATE 'INSERT INTO ' ||  v_tableName || ' (jmeno, prijmeni, narozeni) 
                    SELECT jmeno, prijmeni, narozeni
                    FROM OSOBA
                    WHERE POHLAVI = :1 AND NAROZENI BETWEEN :2 AND :3'
                    USING v_pohlavi.POHLAVI, p_fromDate, p_untilDate;

        EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_tableName INTO v_recordCount;

        DBMS_OUTPUT.PUT_LINE(v_tableName || ': ' || v_recordCount || ' zaznamů');
    END LOOP;

END;




















-- drop table TOO_MANY_INCLUSION_LOG;

CREATE TABLE TOO_MANY_INCLUSION_LOG (
    ID_OSOBA INTEGER, 
    INFO VARCHAR(300), 
    DATUM_PRIDANI TIMESTAMP
);


CREATE OR REPLACE TRIGGER TPreventTooManyInclusion BEFORE INSERT ON ZARAZENI FOR EACH ROW
DECLARE
    v_date DATE;
    v_osoba OSOBA%ROWTYPE;
    v_numberOfInclusion INTEGER;
    v_info VARCHAR(300);
    v_age INTEGER;
BEGIN
    SELECT COUNT(*) INTO v_numberOfInclusion
    FROM ZARAZENI
    WHERE OD_O < :new.DO_O AND DO_O > :new.OD_O AND ID_OSOBA = :new.ID_OSOBA;

    v_numberOfInclusion := v_numberOfInclusion + 1;

    SELECT * INTO v_osoba FROM OSOBA WHERE ID_OSOBA = :new.ID_OSOBA;

    v_age := FLOOR(MONTHS_BETWEEN(CURRENT_DATE, v_osoba.NAROZENI) / 12);

    v_info := v_osoba.JMENO || ' ' || v_osoba.PRIJMENI ||  ' ' || TO_CHAR(v_age) || ' let - ' || TO_CHAR(v_numberOfInclusion) || ' zařazení';

    IF v_numberOfInclusion > FLOOR(v_age / 10) THEN
        INSERT INTO TOO_MANY_INCLUSION_LOG (ID_OSOBA, INFO, DATUM_PRIDANI) VALUES (:new.ID_OSOBA, v_info, CURRENT_TIMESTAMP);
    END IF;

    DBMS_OUTPUT.PUT_LINE(v_info);

    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('osoba nebyla nalezena');

END;













-- A1
ALTER TABLE poslanec
ADD absence_level CHAR(1) DEFAULT 'x' CHECK (absence_level IN ('L', 'M', 'H', 'x'));

CREATE OR REPLACE PROCEDURE SetAbsenceLevel(p_od DATE, p_do DATE) IS
BEGIN
    FOR rec IN (SELECT id_poslanec, COUNT(*) AS pocet_absenci
                FROM omluva
                WHERE den BETWEEN p_od AND p_do
                GROUP BY id_poslanec) LOOP
        UPDATE poslanec
        SET absence_level =
            CASE
                WHEN rec.pocet_absenci < 10 THEN 'L'
                WHEN rec.pocet_absenci BETWEEN 11 AND 20 THEN 'M'
                ELSE 'H'
            END
        WHERE id_poslanec = rec.id_poslanec;
    END LOOP;
    COMMIT;
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
END;

-----------------------------------------------------------------------

-- A2
CREATE OR REPLACE FUNCTION GetConfusedVote(p_id_osoba IN NUMBER) 
RETURN INT IS
    v_pocet_zmatecnych_hlasovani int;
    v_pocet_osob int;
BEGIN
    SELECT COUNT(*) INTO v_pocet_osob
    FROM osoba
    WHERE id_osoba = p_id_osoba;

    IF v_pocet_osob = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Osoba s daným ID neexistuje.');
        RETURN -1;
    END IF;

    -- Spočítání zmatecných hlasování dané osoby v daném roce
    SELECT COUNT(*)
    INTO v_pocet_zmatecnych_hlasovani
    FROM zmatecne_hlasovani_poslanec 
    JOIN hlasovani on zmatecne_hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani
    WHERE id_osoba = p_id_osoba AND 
      EXTRACT(YEAR FROM datum) = EXTRACT(YEAR FROM CURRENT_TIMESTAMP);

    COMMIT;
    RETURN v_pocet_zmatecnych_hlasovani;
EXCEPTION
   WHEN OTHERS THEN
      ROLLBACK;
END;



















-- A1
create or replace procedure p_rozdel_funkce(
    p_funkce_od DATE,
    p_funkce_do DATE
) AS
    v_existuje INT;
    v_zarazeni ZARAZENI%rowtype;
    v_cnt_ins INT := 0;
    v_cnt INT;
    ex_CAS_INVALID EXCEPTION ;
BEGIN
    SELECT COUNT(*)
    into v_existuje
    FROM USER_TABLES
    where TABLE_NAME = 'ZARAZENI_FUNKCE';

    IF v_existuje > 0 THEN
        EXECUTE IMMEDIATE 'DROP TABLE ZARAZENI_FUNKCE';
    END IF;

    if p_funkce_od >= p_funkce_do OR (p_funkce_do > CURRENT_DATE) THEN
        raise ex_CAS_INVALID;
    end if;

    execute immediate 'create table ZARAZENI_FUNKCE
        (id_osoba INT REFERENCES OSOBA, id_funkce INT REFERENCES FUNKCE, funkce_od DATE, funkce_do DATE)';

    select count(*) into v_cnt
    FROM ZARAZENI WHERE OD_F >= p_funkce_od AND DO_F <= p_funkce_do AND CL_FUNKCE=1;

    FOR v_zarazeni IN (SELECT * FROM ZARAZENI WHERE OD_F >= p_funkce_od AND DO_F <= p_funkce_do AND CL_FUNKCE=1) LOOP
        EXECUTE IMMEDIATE 'INSERT INTO ZARAZENI_FUNKCE(id_osoba, id_funkce, funkce_od, funkce_do) VALUES (:1, :2, :3, :4)'
        USING v_zarazeni.ID_OSOBA, v_zarazeni.ID_OF, v_zarazeni.OD_F, v_zarazeni.DO_F;
        v_cnt_ins := v_cnt_ins + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Vlozeno ' || v_cnt_ins || ' zaznamu z ' || v_cnt);
exception
    when ex_CAS_INVALID THEN
        DBMS_OUTPUT.PUT_LINE('Spatne zadane parametry p_funkce_od nebo p_funkce_do');
END;

begin
    -- chyba pro spatne casy p_funkce_od a p_funkce_do
    p_rozdel_funkce(to_date('2024-02-01', 'YYYY-MM-DD'), to_date('2022-02-01', 'YYYY-MM-DD'));
    -- OUTPUT: Spatne zadane parametry p_funkce_od nebo p_funkce_do
    -- chyba pro budoucni cas parametru p_funkce_do
    p_rozdel_funkce(to_date('2022-02-01', 'YYYY-MM-DD'), to_date('2025-02-01', 'YYYY-MM-DD'));
    -- OUTPUT: Spatne zadane parametry p_funkce_od nebo p_funkce_do
    -- Spravne volani
    p_rozdel_funkce(to_date('2008-01-01', 'YYYY-MM-DD'), to_date('2022-12-31', 'YYYY-MM-DD'));
    -- OUTPUT: Vlozeno 30 zaznamu z 30
end;


-- A2
create or replace procedure p_poslanec_omluv(
    p_poslanec_id INT,
    p_od OMLUVA.od%TYPE,
    p_do OMLUVA.do%TYPE
) as
    v_poslanec_cnt  int;
    v_hlasovani_cnt int;
    v_omluven_cnt   int;
    v_id_organ      OMLUVA.id_organ%TYPE;

    ex_poslanec EXCEPTION ;
    ex_hlasovani EXCEPTION ;
    ex_omluven EXCEPTION ;
    ex_cas EXCEPTION ;
begin
    select count(*) into v_poslanec_cnt from POSLANEC where ID_POSLANEC = p_poslanec_id;
    select count(*)
    into v_omluven_cnt
    from OMLUVA
    where ID_POSLANEC = p_poslanec_id
      AND to_char(p_od, 'YYYY-MM-DD') = to_char(den, 'YYYY-MM-DD');

    if v_poslanec_cnt <= 0 then
        raise ex_poslanec;
    elsif p_od > p_do then
        raise ex_cas;
    elsif v_omluven_cnt > 0 then
        raise ex_omluven;
    end if;

    select ID_ORGAN into v_id_organ from POSLANEC where ID_POSLANEC = p_poslanec_id;

    insert into OMLUVA(ID_ORGAN, ID_POSLANEC, DEN, OD, DO)
    VALUES (v_id_organ, p_poslanec_id, CAST(p_od AS DATE), p_od, p_do);

    select count(*)
    into v_hlasovani_cnt
    from HLASOVANI
             join HLASOVANI_POSLANEC hp on HLASOVANI.ID_HLASOVANI = hp.ID_HLASOVANI
    where hp.ID_POSLANEC = p_poslanec_id
      AND to_char(p_od, 'YYYY-MM-DD') = to_char(datum, 'YYYY-MM-DD')
      and to_char(cas, 'HH24:MI:SS') between to_char(p_od, 'HH24:MI:SS') and to_char(p_do, 'HH24:MI:SS');
    if v_hlasovani_cnt > 0 THEN
        raise ex_hlasovani;
    end if;

    commit;
    DBMS_OUTPUT.PUT_LINE('Omluva zaznamenana.');
exception
    when ex_poslanec then
        DBMS_OUTPUT.PUT_LINE('Poslanec neexistuje!');
    when ex_omluven then
        DBMS_OUTPUT.PUT_LINE('Poslanec je jiz omluven!');
    when ex_cas then
        DBMS_OUTPUT.PUT_LINE('Hodnota DO je mensi nez hodnota OD');
    when ex_hlasovani then
        DBMS_OUTPUT.PUT_LINE('Poslanec ma v dane dobe hlasovani a nemuze byt omluven');
        rollback;
end;


declare
    v_od TIMESTAMP := to_timestamp('2024-03-01 09:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do TIMESTAMP := to_timestamp('2024-03-01 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
begin
    -- chyba pro neexistujiciho poslance
    p_poslanec_omluv(2050, v_od, v_do);
    -- OUTPUT: Poslanec neexistuje!
    v_do := to_timestamp('2024-03-01 09:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_od := to_timestamp('2024-03-01 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba pro spatne casy
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Hodnota DO je mensi nez hodnota OD
    v_od := to_timestamp('2023-09-15 13:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do := to_timestamp('2023-09-15 14:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba - poslanec uz je omluveny
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Poslanec je jiz omluven!
    v_od := to_timestamp('2023-09-26 13:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do := to_timestamp('2023-09-26 15:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba - poslanec v te dobe hlasoval
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Poslanec ma v dane dobe hlasovani a nemuze byt omluven
    v_od := to_timestamp('2024-01-01 13:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do := to_timestamp('2024-01-01 15:00:00', 'YYYY-MM-DD HH24:MI:SS');
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Omluva zaznamenana.
end;


-- B1
create or replace procedure p_rozdel_organ(
    p_organ_od DATE,
    p_organ_do DATE
) AS
    v_existuje INT;
    v_zarazeni ZARAZENI%rowtype;
    v_cnt_ins INT := 0;
    v_cnt INT;
    ex_CAS_INVALID EXCEPTION ;
BEGIN
    SELECT COUNT(*)
    into v_existuje
    FROM USER_TABLES
    where TABLE_NAME = 'ZARAZENI_ORGAN';

    IF v_existuje > 0 THEN
        EXECUTE IMMEDIATE 'DROP TABLE ZARAZENI_ORGAN';
    END IF;

    if p_organ_od >= p_organ_do OR (p_organ_do > CURRENT_DATE) THEN
        raise ex_CAS_INVALID;
    end if;

    execute immediate 'create table ZARAZENI_ORGAN
        (id_osoba INT REFERENCES OSOBA, id_organ INT REFERENCES ORGAN, organ_od DATE, organ_do DATE)';

    select count(*) into v_cnt
    FROM ZARAZENI WHERE OD_F >= p_organ_od AND DO_F <= p_organ_do AND CL_FUNKCE=0;

    FOR v_zarazeni IN (SELECT * FROM ZARAZENI WHERE OD_F >= p_organ_od AND DO_F <= p_organ_do AND CL_FUNKCE=0) LOOP
        EXECUTE IMMEDIATE 'INSERT INTO ZARAZENI_ORGAN(id_osoba, ID_ORGAN, organ_od, organ_do) VALUES (:1, :2, :3, :4)'
        USING v_zarazeni.ID_OSOBA, v_zarazeni.ID_OF, v_zarazeni.OD_F, v_zarazeni.DO_F;
        v_cnt_ins := v_cnt_ins + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Vlozeno ' || v_cnt_ins || ' zaznamu z ' || v_cnt);
exception
    when ex_CAS_INVALID THEN
        DBMS_OUTPUT.PUT_LINE('Spatne zadane parametry p_organ_od nebo p_organ_do');
END;



-- B2
create or replace procedure p_poslanec_hlasuj(
    p_poslanec_id HLASOVANI_POSLANEC.ID_POSLANEC%TYPE,
    p_hlasovani_id HLASOVANI_POSLANEC.ID_HLASOVANI%TYPE,
    p_cas HLASOVANI.CAS%TYPE,
    p_vysledek HLASOVANI_POSLANEC.VYSLEDEK%TYPE
) as
    v_poslanec_cnt  int;
    v_hlasovani_cnt int;
    v_omluven       INT;

    ex_poslanec EXCEPTION ;
    ex_hlasovani EXCEPTION ;
    ex_cas EXCEPTION ;
    ex_vysledek EXCEPTION ;
    ex_omluven EXCEPTION ;
begin
    select count(*) into v_poslanec_cnt from POSLANEC where ID_POSLANEC = p_poslanec_id;
    select count(*)
    into v_hlasovani_cnt
    from HLASOVANI
    where ID_HLASOVANI = p_hlasovani_id;

    if v_poslanec_cnt <= 0 then
        raise ex_poslanec;
    elsif v_hlasovani_cnt <= 0 then
        raise ex_hlasovani;
    elsif p_vysledek NOT IN ('A', 'B', 'X') then
        raise ex_vysledek;
    elsif p_cas > CURRENT_TIMESTAMP THEN
        raise ex_cas;
    end if;

    select count(*)
    into v_omluven
    from OMLUVA
    where ID_POSLANEC = p_poslanec_id
      and to_char(den, 'YYYY-MM-DD') = to_char(p_cas, 'YYYY-MM-DD')
      and to_char(p_cas, 'HH24:MI:SS') between to_char(od, 'HH24:MI:SS') and to_char(do, 'HH24:MI:SS');

    if v_omluven > 0 then
        raise ex_omluven;
    end if;

    delete from HLASOVANI_POSLANEC
    where ID_HLASOVANI=p_hlasovani_id and ID_POSLANEC=p_poslanec_id;

    insert into HLASOVANI_POSLANEC(ID_POSLANEC, ID_HLASOVANI, VYSLEDEK)
    VALUES (p_poslanec_id, p_hlasovani_id, p_vysledek);

    update HLASOVANI
    set PRO = PRO + CASE WHEN p_vysledek = 'A' THEN 1 else 0 END,
        PROTI=PROTI + CASE WHEN p_vysledek = 'B' THEN 1 else 0 END,
        ZDRZEL=ZDRZEL + CASE WHEN p_vysledek = 'X' THEN 1 else 0 END
    where ID_HLASOVANI = p_hlasovani_id;
    DBMS_OUTPUT.PUT_LINE('Hlasování bylo zaznamenáno.');
    commit;
exception
    when ex_poslanec then
        DBMS_OUTPUT.PUT_LINE('Poslanec neexistuje!');
    when ex_hlasovani then
        DBMS_OUTPUT.PUT_LINE('Hlasování neexistujte');
    when ex_vysledek then
        DBMS_OUTPUT.PUT_LINE('Výsledek nemá platnou hodnotu');
    when ex_cas then
        DBMS_OUTPUT.PUT_LINE('Čas hlasování je v budoucnosti!');
    when ex_omluven then
        DBMS_OUTPUT.PUT_LINE('Poslanec je na dané hlasování omluven!');
        rollback;
end;

declare
    v_cas TIMESTAMP := to_timestamp('2023-09-06 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
begin
    -- chyba pro neexistujiciho poslance
    p_poslanec_hlasuj(2050, 81531, v_cas, 'X');
    -- OUTPUT: Poslanec neexistuje!
    -- chyba pro neexistujici hlasovani
    p_poslanec_hlasuj(1940, 100000, v_cas, 'B');
    -- OUTPUT: Hlasování neexistujte
    -- chyba - spatny vysledek
    p_poslanec_hlasuj(1940, 81531, v_cas, 'Z');
    -- OUTPUT: Výsledek nemá platnou hodnotu
    -- chyba - poslanec je v dany cas omluven
    p_poslanec_hlasuj(1940, 81531, v_cas, 'A');
    -- OUTPUT: Poslanec je na dané hlasování omluven!
    v_cas := to_timestamp('2025-09-06 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba - hlasovani v budoucnu
    p_poslanec_hlasuj(1940, 81531, v_cas, 'A');
    -- OUTPUT: Čas hlasování je v budoucnosti!
    v_cas := to_timestamp('2023-09-26 14:18:00', 'YYYY-MM-DD HH24:MI:SS');
    p_poslanec_hlasuj(1940, 81531, v_cas, 'A');
    -- OUTPUT: Hlasování bylo zaznamenáno.
end;























-- A1

create or replace PROCEDURE P_SET_ZARAZENI_ORG(p_id_osoba INT, p_id_organ INT, p_set CHAR) AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM organ
    WHERE id_organ = p_id_organ;

    IF v_cnt = 0 THEN
        dbms_output.put_line('Neplatne ID organu');
        RETURN;
    END IF;

    SELECT COUNT(*) INTO v_cnt
    FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
        VALUES (p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
        DELETE FROM zarazeni
        WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;
    END IF;

END;

/

BEGIN
    P_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    P_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    P_SET_ZARAZENI_ORG(6755, 1229, 'N');
    P_SET_ZARAZENI_ORG(6755, 1229, 'N');
END;


-- A2

create or replace TRIGGER TG_HLASOVANI_POSLANEC AFTER INSERT OR UPDATE OR DELETE ON HLASOVANI_POSLANEC FOR EACH ROW
BEGIN
    IF :old.vysledek = 'A' THEN 
        UPDATE hlasovani
        SET pro = pro - 1
        WHERE hlasovani.id_hlasovani = :old.id_hlasovani;
    END IF;

    IF :old.vysledek = 'B' THEN 
        UPDATE hlasovani
        SET proti = proti - 1
        WHERE hlasovani.id_hlasovani = :old.id_hlasovani;
    END IF;

    IF :new.vysledek = 'A' THEN 
        UPDATE hlasovani
        SET pro = pro + 1
        WHERE hlasovani.id_hlasovani = :new.id_hlasovani;
    END IF;

    IF :new.vysledek = 'B' THEN 
        UPDATE hlasovani
        SET proti = proti + 1
        WHERE hlasovani.id_hlasovani = :new.id_hlasovani;
    END IF;
END;

/

DECLARE
    v_pro INT;
    v_proti INT;
BEGIN

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1
    
    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    UPDATE hlasovani_poslanec
    SET vysledek = 'B'
    WHERE id_poslanec = 1942 AND id_hlasovani = 81577;
    
    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 112, proti: 2

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    UPDATE hlasovani_poslanec
    SET vysledek = 'A'
    WHERE id_poslanec = 1942 AND id_hlasovani = 81577;

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
END;

-- B1

create or replace PROCEDURE P_SET_HLASOVANI_POSLANEC(p_id_hlasovani INT, p_id_poslanec INT, p_vysledek CHAR) AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM hlasovani_poslanec
    WHERE id_poslanec = p_id_poslanec AND id_hlasovani = p_id_hlasovani;

    IF v_cnt = 0 THEN
        INSERT INTO hlasovani_poslanec(id_poslanec, id_hlasovani, vysledek)
        VALUES (p_id_poslanec, p_id_hlasovani, p_vysledek);
    ELSE
        UPDATE hlasovani_poslanec
        SET vysledek = p_vysledek
        WHERE id_poslanec = p_id_poslanec AND id_hlasovani = p_id_hlasovani;
    END IF;

    UPDATE hlasovani
    SET pro = (
        SELECT COUNT(*)
        FROM hlasovani_poslanec
        WHERE id_hlasovani = p_id_hlasovani AND vysledek = 'A'
    )
    WHERE id_hlasovani = p_id_hlasovani;

    UPDATE hlasovani
    SET proti = (
        SELECT COUNT(*)
        FROM hlasovani_poslanec
        WHERE id_hlasovani = p_id_hlasovani AND vysledek = 'B'
    )
    WHERE id_hlasovani = p_id_hlasovani;
END;

/

DECLARE
    v_pro INT;
    v_proti INT;
BEGIN

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1
    
    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    P_SET_HLASOVANI_POSLANEC(81577, 1942, 'B');
    
    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 112, proti: 2

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    P_SET_HLASOVANI_POSLANEC(81577, 1942, 'A');

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
END;

-- B2

create or replace FUNCTION F_SET_ZARAZENI_ORG(p_id_osoba INT, p_id_organ INT, p_set CHAR) RETURN CHAR AS
    v_cnt INT;
    v_ret CHAR(1);
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM organ
    WHERE id_organ = p_id_organ;

    IF v_cnt = 0 THEN
        dbms_output.put_line('Neplatne ID organu');
        RETURN 'E';
    END IF;

    SELECT COUNT(*) INTO v_cnt
    FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
        VALUES (p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);

        RETURN 'I';
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
        DELETE FROM zarazeni
        WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

        RETURN 'D';
    ELSE
        RETURN 'N';
    END IF;
END;

/

DECLARE
    v_ret CHAR(1);
BEGIN
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'N');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'N');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 12290, 'Y');
    dbms_output.put_line(v_ret);
END;



























-- A1

create or replace TRIGGER TG_ZARAZENI 
BEFORE INSERT OR UPDATE ON zarazeni FOR EACH ROW
DECLARE
    v_cnt INT;
    v_ex EXCEPTION;
BEGIN
    IF :new.cl_funkce = 0 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM organ
        WHERE id_organ = :new.id_of;

        IF v_cnt = 0 THEN
            dbms_output.put_line('Invalid id_organ.');
            RAISE v_ex;
        END IF;
    ELSIF :new.cl_funkce = 1 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM funkce
        WHERE id_funkce = :new.id_of;

        IF v_cnt = 0 THEN
            dbms_output.put_line('Invalid id_funkce.');
            RAISE v_ex;
        END IF;    
    ELSE
        dbms_output.put_line('Invalid cl_funkce.');
        RAISE v_ex;
    END IF;

    -- Pripadne elegantnejsi reseni by bylo raise_application_error( -20001, 'This is a custom error' );.
END;

/

-- Priklad vlozeni OK:
INSERT INTO Zarazeni(id_osoba, id_of, cl_funkce, od_o)
VALUES (6755, 1229, 0, CURRENT_TIMESTAMP);

-- Priklad neplatne ID funkce.
INSERT INTO Zarazeni(id_osoba, id_of, cl_funkce, od_o)
VALUES (6755, 1229, 1, CURRENT_TIMESTAMP);

-- Priklad neplatne cl_funkce.
INSERT INTO Zarazeni(id_osoba, id_of, cl_funkce, od_o)
VALUES (6755, 1229, 2, CURRENT_TIMESTAMP);

-- A2


create or replace PROCEDURE P_PRINT_HLASOVANI(p_id_hlasovani INT) AS
    v_prev_vysledek CHAR(1) := ' ';
BEGIN
    FOR v_rec IN (
        SELECT hp.vysledek, o.jmeno, o.prijmeni
        FROM
            hlasovani_poslanec hp
            JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
            JOIN osoba o ON p.id_osoba = o.id_osoba
        WHERE hp.id_hlasovani = p_id_hlasovani
        ORDER BY hp.vysledek) LOOP

        IF v_rec.vysledek != v_prev_vysledek THEN
            dbms_output.put_line('vysledek ' || v_rec.vysledek || ':');
            v_prev_vysledek := v_rec.vysledek;
        END IF;

        dbms_output.put_line('  * ' || v_rec.jmeno || ' ' || v_rec.prijmeni);
    END LOOP;
END;

/

BEGIN
    P_PRINT_HLASOVANI(29714);
END;

-- B1

create or replace PROCEDURE P_SET_ZARAZENI_FCE(p_id_osoba INT, p_id_funkce INT, p_set CHAR) AS
    v_cnt INT;
    v_ex EXCEPTION;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM funkce
    WHERE id_funkce = p_id_funkce;

    IF v_cnt = 0 THEN
        dbms_output.put_line('Neplatne ID funkce');
        RAISE v_ex;
    END IF;

    SELECT COUNT(*) INTO v_cnt
    FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_funkce AND cl_funkce = 1;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
        VALUES (p_id_osoba, p_id_funkce, 1, CURRENT_TIMESTAMP);

        dbms_output.put_line('Nastaveno zarazeni osoby do funke.');
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
        DELETE FROM zarazeni
        WHERE id_osoba = p_id_osoba AND id_of = p_id_funkce AND cl_funkce = 1;

        dbms_output.put_line('Zruseno zarazeni osoby z funke.');
    ELSE
        dbms_output.put_line('Nebyla provedena zadna operace.');
    END IF;

END;

/

BEGIN
    P_SET_ZARAZENI_FCE(6755, 2930, 'Y');
    P_SET_ZARAZENI_FCE(6755, 2930, 'Y');
    P_SET_ZARAZENI_FCE(6755, 2930, 'N');
    P_SET_ZARAZENI_FCE(6755, 2930, 'N');
END;

-- B2

create or replace FUNCTION F_COPY_SCHUZE(p_id_schuze INT, p_od_schuze DATE, p_do_schuze DATE) RETURN INT AS
    v_id_organ INT;
    v_id_schuze_new INT;
    v_schuze_new INT;
BEGIN
    SELECT id_organ INTO v_id_organ
    FROM schuze
    WHERE id_schuze = p_id_schuze;

    SELECT COALESCE(MAX(id_schuze), 0) + 1 INTO v_id_schuze_new
    FROM schuze;

    SELECT COALESCE(MAX(schuze), 0) + 1 INTO v_schuze_new
    FROM schuze
    WHERE id_organ = v_id_organ;

    INSERT INTO schuze (id_schuze, id_organ, schuze, od_schuze, do_schuze, aktualizace)
    SELECT v_id_schuze_new, id_organ, v_schuze_new, p_od_schuze, p_do_schuze, aktualizace
    FROM schuze
    WHERE id_schuze = p_id_schuze;

    INSERT INTO bod_schuze (id_bod, id_schuze, id_tisk, id_typ, bod, uplny_naz, uplny_kon, poznamka, id_bod_stav, pozvanka, rj, pozn2, druh_bodu, id_sd, zkratka)
    SELECT id_bod, v_id_schuze_new, id_tisk, id_typ, bod, uplny_naz || ' (kopie)', uplny_kon, poznamka, id_bod_stav, pozvanka, rj, pozn2, druh_bodu, id_sd, zkratka
    FROM bod_schuze
    WHERE id_schuze = p_id_schuze;

    RETURN v_id_schuze_new;
END;

/

DECLARE
    v_id_schuze_new INT;
    v_pocet_bodu INT;
BEGIN
    v_id_schuze_new := F_COPY_SCHUZE(734, TO_DATE('2024-03-28', 'yyyy-mm-dd'), TO_DATE('2024-03-29', 'yyyy-mm-dd'));
    dbms_output.put_line('ID nove schuze: ' || TO_CHAR(v_id_schuze_new));
    
    SELECT COUNT(*) INTO v_pocet_bodu
    FROM bod_schuze
    WHERE id_schuze = v_id_schuze_new;
    
    dbms_output.put_line('Pocet zkopirovaych bodu: ' || TO_CHAR(v_pocet_bodu));
END;