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
