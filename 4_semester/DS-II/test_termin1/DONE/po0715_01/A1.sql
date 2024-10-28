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
