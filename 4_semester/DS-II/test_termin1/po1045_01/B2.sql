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
