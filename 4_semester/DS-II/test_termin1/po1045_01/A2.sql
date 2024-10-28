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
