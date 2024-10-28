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