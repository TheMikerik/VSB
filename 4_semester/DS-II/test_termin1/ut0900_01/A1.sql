
CREATE OR REPLACE PROCEDURE PBackupPoslanec(p_idOrgan INTEGER)
IS
    v_backupTableName VARCHAR(50);
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_backupExistsException EXCEPTION;
BEGIN

    v_backupTableName := 'OSOBA_BACKUP_' || p_idOrgan;
     
    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = v_backupTableName;
    
    IF v_tableCount > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Záloha již existuje!');
        RAISE v_backupExistsException;
    END IF;

    v_createTable := 'create table ' || v_backupTableName || ' (
        id_osoba INT NOT NULL,
        pred VARCHAR(30) NULL,
        prijmeni VARCHAR(100) NULL,
        jmeno VARCHAR(100) NULL,
        za VARCHAR(255) NULL,
        narozeni DATE NULL,
        pohlavi CHAR(2) NULL,
        zmena DATE NULL,
        umrti DATE NULL,
        CONSTRAINT osoba' || p_idOrgan || '_pk PRIMARY KEY (id_osoba)
    )';
    
    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO ' || v_backupTableName || ' SELECT o.* FROM OSOBA o 
        INNER JOIN POSLANEC p 
            ON o.ID_OSOBA=p.ID_OSOBA
        WHERE p.ID_ORGAN=:1' USING p_idOrgan;

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_backupTableName INTO v_tableCount;

    DBMS_OUTPUT.PUT_LINE('Počet zálohovaných osob: ' || v_tableCount);
    
END;
