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

