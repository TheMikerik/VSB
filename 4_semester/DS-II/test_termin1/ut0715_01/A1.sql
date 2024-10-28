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
