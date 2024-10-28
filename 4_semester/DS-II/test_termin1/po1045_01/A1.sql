CREATE OR REPLACE PROCEDURE PCreateOsoba2(p_minBornDate VARCHAR, p_maxBornDate VARCHAR)
IS
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_count INTEGER;
    v_invalidRangeException EXCEPTION;
BEGIN

    IF TO_DATE(p_minBornDate, 'YYYY-MM-DD') > TO_DATE(p_maxBornDate, 'YYYY-MM-DD') THEN
        DBMS_OUTPUT.PUT_LINE('Špatné zadané časové rozmezí:' || p_minBornDate || ' - ' || p_maxBornDate);
        RAISE v_invalidRangeException;
    END IF;

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = 'OSOBA2';
    
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table OSOBA2';
    END IF;

    v_createTable := 'create table osoba2 (
        id_osoba INT NOT NULL,
        pred VARCHAR(30) NULL,
        prijmeni VARCHAR(100) NULL,
        jmeno VARCHAR(100) NULL,
        za VARCHAR(255) NULL,
        narozeni DATE NULL,
        pohlavi CHAR(2) NULL,
        zmena DATE NULL,
        umrti DATE NULL,
        CONSTRAINT osoba2_pk PRIMARY KEY (id_osoba)
    )';
    
    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO OSOBA2 SELECT * FROM osoba WHERE narozeni BETWEEN :1 AND :2' USING TO_DATE(p_minBornDate, 'YYYY-MM-DD'), TO_DATE(p_maxBornDate, 'YYYY-MM-DD');

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM OSOBA2' INTO v_count;

    DBMS_OUTPUT.PUT_LINE('Počet zkopírovaných záznamů: ' || v_count);
END;

