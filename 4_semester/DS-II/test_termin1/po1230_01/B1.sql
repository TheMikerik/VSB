



CREATE OR REPLACE PROCEDURE POpravOmluva
IS
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_zarazeni INTEGER;
BEGIN

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = 'OMLUVA_FIXED';
    
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table Omluva_fixed';
    END IF;

    v_createTable := 'create table Omluva_fixed (
    id_organ INT NOT NULL,
    id_poslanec INT NOT NULL,
    od TIMESTAMP NULL,
    do TIMESTAMP NULL,
    CONSTRAINT omluva_fixed_fk_id_organ FOREIGN KEY (id_organ) REFERENCES organ (id_organ),
    CONSTRAINT omluva_fixed_fk_id_poslanec FOREIGN KEY (id_poslanec) REFERENCES poslanec (id_poslanec)
    )';

    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO Omluva_fixed SELECT 
        id_organ, 
        id_poslanec,
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' 00:00:00'', ''YYYY-MM-DD HH24:MI:SS''), 
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' 23:59:59'', ''YYYY-MM-DD HH24:MI:SS'')
     FROM Omluva WHERE od IS NULL AND do IS NULL';
    
    EXECUTE IMMEDIATE 'INSERT INTO Omluva_fixed SELECT 
        id_organ, 
        id_poslanec,
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' '' || TO_CHAR(OD, ''HH24:MI:SS''), ''YYYY-MM-DD HH24:MI:SS''), 
        TO_TIMESTAMP(TO_CHAR(DEN, ''YYYY-MM-DD'') || '' '' || TO_CHAR(DO, ''HH24:MI:SS''), ''YYYY-MM-DD HH24:MI:SS'')
     FROM Omluva WHERE od IS NOT NULL AND do IS NOT NULL';

END;

