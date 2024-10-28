CREATE OR REPLACE PROCEDURE PCreateSchuze(p_idOrgan ORGAN.ID_ORGAN%TYPE)
IS
    v_organ ORGAN%ROWTYPE;

    v_tableName VARCHAR(50);
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_count INTEGER;
BEGIN

    SELECT * INTO v_organ FROM ORGAN WHERE ID_ORGAN = p_idOrgan;

    DBMS_OUTPUT.PUT_LINE('Orgán:' || v_organ.nazev_organu_cz || ' (' || v_organ.ZKRATKA || ')');

    v_tableName := 'SCHUZE_' || TO_CHAR(p_idOrgan);

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = v_tableName;
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table ' || v_tableName;
    END IF;

    v_createTable := 'create table ' || v_tableName || ' (
        id_schuze INT NOT NULL,
        id_organ INT NULL,
        schuze INT NULL,
        od_schuze TIMESTAMP NULL,
        do_schuze TIMESTAMP NULL,
        aktualizace TIMESTAMP NULL,
        CONSTRAINT schuze' || TO_CHAR(p_idOrgan) || '_pk PRIMARY KEY (id_schuze),
        CONSTRAINT schuze' || TO_CHAR(p_idOrgan) || '_uniq UNIQUE(id_organ, schuze),
        CONSTRAINT schuze' || TO_CHAR(p_idOrgan) || '_fk_id_organ FOREIGN KEY (id_organ) REFERENCES organ (id_organ)
    )';

    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO ' || v_tableName || ' SELECT * FROM SCHUZE WHERE ID_ORGAN = :1' USING p_idOrgan;

    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM ' || v_tableName INTO v_count;

    DBMS_OUTPUT.PUT_LINE('Počet zkopírovaných záznamů: ' || v_count);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Orgán nenalezen.');
END;

