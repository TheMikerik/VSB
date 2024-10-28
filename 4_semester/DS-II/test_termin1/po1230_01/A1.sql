CREATE OR REPLACE PROCEDURE POpravZarazeni(p_fromDate DATE, p_untilDate DATE)
IS
    v_createTable VARCHAR(800);
    v_tableCount INTEGER;
    v_zarazeni INTEGER;
BEGIN

    SELECT COUNT(*) INTO v_tableCount FROM user_tables WHERE table_name = 'ZARAZENI_FIXED';
    
    IF v_tableCount > 0 THEN
        EXECUTE IMMEDIATE 'drop table Zarazeni_fixed';
    END IF;

    v_createTable := 'create table Zarazeni_fixed (
        id_osoba INT NULL,
        id_organ INT NULL,
        id_funkce INT NULL,
        od_o DATE NULL,
        do_o DATE NULL,
        od_f DATE NULL,
        do_f DATE NULL,
        CONSTRAINT zarazeni_fixed_fk_id_osoba FOREIGN KEY (id_osoba) REFERENCES osoba (id_osoba),
        CONSTRAINT zarazeni_fixed_fk_id_organ FOREIGN KEY (id_organ) REFERENCES organ (id_organ),
        CONSTRAINT zarazeni_fixed_fk_id_funkce FOREIGN KEY (id_funkce) REFERENCES funkce (id_funkce)
    )';


    EXECUTE IMMEDIATE v_createTable;

    EXECUTE IMMEDIATE 'INSERT INTO Zarazeni_fixed SELECT id_osoba, id_of, null, od_o, do_o, od_f, do_f FROM Zarazeni where cl_funkce=0';
    EXECUTE IMMEDIATE 'INSERT INTO Zarazeni_fixed SELECT id_osoba, null, id_of, od_o, do_o, od_f, do_f FROM Zarazeni where cl_funkce=1';
    
    EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM Zarazeni_fixed WHERE id_organ is not null and OD_O > :1 AND DO_O < :2' INTO v_zarazeni USING p_fromDate, p_untilDate;
    
    DBMS_OUTPUT.PUT_LINE('Počet zařazení do orgánů v době od ' || p_fromDate || ' do ' || p_untilDate || ': ' || v_zarazeni);

END;
