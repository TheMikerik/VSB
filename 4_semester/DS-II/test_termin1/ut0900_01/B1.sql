
CREATE OR REPLACE PROCEDURE PBackupZarazeni(p_idPoslanec INTEGER)
IS
    v_osoba OSOBA%ROWTYPE;
    v_backupTableName VARCHAR(50);
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_backupExistsException EXCEPTION;
BEGIN

    SELECT o.* INTO v_osoba FROM POSLANEC p INNER JOIN OSOBA o ON o.ID_OSOBA=p.ID_OSOBA WHERE p.ID_POSLANEC = p_idPoslanec;

    DBMS_OUTPUT.PUT_LINE('Osoba:' || v_osoba.JMENO || ' ' || v_osoba.PRIJMENI);

    v_backupTableName := 'ZARAZENI_BACKUP_' || p_idPoslanec;
     
    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = v_backupTableName;
    
    IF v_tableCount > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Záloha již existuje!');
        RAISE v_backupExistsException;
    END IF;

    v_createTable := 'create table ' || v_backupTableName || ' (
        id_osoba INT NULL,
        id_of INT NULL,
        cl_funkce INT NULL,
        od_o DATE NULL,
        do_o DATE NULL,
        od_f DATE NULL,
        do_f DATE NULL,
        CONSTRAINT zarazeni_fk_id_osoba' || p_idPoslanec || ' FOREIGN KEY (id_osoba) REFERENCES osoba (id_osoba)
    )';

    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO ' || v_backupTableName || ' SELECT z.* FROM ZARAZENI z WHERE z.ID_OSOBA = :1' USING v_osoba.ID_OSOBA;

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_backupTableName INTO v_tableCount;

    DBMS_OUTPUT.PUT_LINE('Počet zálohovaných zařazení: ' || v_tableCount);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Záloha selhala, poslanec neexistuje.');
END;

