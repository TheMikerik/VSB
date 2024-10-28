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

