
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
