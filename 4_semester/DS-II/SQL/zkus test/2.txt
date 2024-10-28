create or replace PROCEDURE P_TEST_2 AS
    v_sql VARCHAR2(1000);
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM USER_TAB_COLUMNS
    WHERE TABLE_NAME = 'HLASOVANI' AND COLUMN_NAME = 'ZMATECNE';

    IF v_cnt = 0 THEN
        v_sql := 'ALTER TABLE HLASOVANI ADD zmatecne CHAR(1)';
        EXECUTE IMMEDIATE v_sql;
    END IF;

    v_sql := 'UPDATE Hlasovani SET zmatecne = 1 WHERE id_hlasovani IN (SELECT id_hlasovani FROM Zmatecne)';
    EXECUTE IMMEDIATE v_sql;

    v_sql := 'UPDATE Hlasovani SET zmatecne = 0 WHERE id_hlasovani NOT IN (SELECT id_hlasovani FROM Zmatecne)';
    EXECUTE IMMEDIATE v_sql;    

    -- Urcite zadny kurzor! V tomto pripade by pouziti kurzoru bylo na testu povazovano za chybu.

    v_sql := 'DROP TABLE Zmatecne';
    EXECUTE IMMEDIATE v_sql;  
END;

