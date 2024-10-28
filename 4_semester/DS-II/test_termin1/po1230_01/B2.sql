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
