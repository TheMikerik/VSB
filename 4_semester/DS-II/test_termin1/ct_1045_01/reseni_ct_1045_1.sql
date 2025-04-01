-- A1

create or replace PROCEDURE P_SET_ZARAZENI_ORG(p_id_osoba INT, p_id_organ INT, p_set CHAR) AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM organ
    WHERE id_organ = p_id_organ;

    IF v_cnt = 0 THEN
        dbms_output.put_line('Neplatne ID organu');
        RETURN;
    END IF;

    SELECT COUNT(*) INTO v_cnt
    FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
        VALUES (p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
        DELETE FROM zarazeni
        WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;
    END IF;

END;

/

BEGIN
    P_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    P_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    P_SET_ZARAZENI_ORG(6755, 1229, 'N');
    P_SET_ZARAZENI_ORG(6755, 1229, 'N');
END;


-- A2

create or replace TRIGGER TG_HLASOVANI_POSLANEC AFTER INSERT OR UPDATE OR DELETE ON HLASOVANI_POSLANEC FOR EACH ROW
BEGIN
    IF :old.vysledek = 'A' THEN 
        UPDATE hlasovani
        SET pro = pro - 1
        WHERE hlasovani.id_hlasovani = :old.id_hlasovani;
    END IF;

    IF :old.vysledek = 'B' THEN 
        UPDATE hlasovani
        SET proti = proti - 1
        WHERE hlasovani.id_hlasovani = :old.id_hlasovani;
    END IF;

    IF :new.vysledek = 'A' THEN 
        UPDATE hlasovani
        SET pro = pro + 1
        WHERE hlasovani.id_hlasovani = :new.id_hlasovani;
    END IF;

    IF :new.vysledek = 'B' THEN 
        UPDATE hlasovani
        SET proti = proti + 1
        WHERE hlasovani.id_hlasovani = :new.id_hlasovani;
    END IF;
END;

/

DECLARE
    v_pro INT;
    v_proti INT;
BEGIN

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1
    
    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    UPDATE hlasovani_poslanec
    SET vysledek = 'B'
    WHERE id_poslanec = 1942 AND id_hlasovani = 81577;
    
    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 112, proti: 2

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    UPDATE hlasovani_poslanec
    SET vysledek = 'A'
    WHERE id_poslanec = 1942 AND id_hlasovani = 81577;

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
END;

-- B1

create or replace PROCEDURE P_SET_HLASOVANI_POSLANEC(p_id_hlasovani INT, p_id_poslanec INT, p_vysledek CHAR) AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM hlasovani_poslanec
    WHERE id_poslanec = p_id_poslanec AND id_hlasovani = p_id_hlasovani;

    IF v_cnt = 0 THEN
        INSERT INTO hlasovani_poslanec(id_poslanec, id_hlasovani, vysledek)
        VALUES (p_id_poslanec, p_id_hlasovani, p_vysledek);
    ELSE
        UPDATE hlasovani_poslanec
        SET vysledek = p_vysledek
        WHERE id_poslanec = p_id_poslanec AND id_hlasovani = p_id_hlasovani;
    END IF;

    UPDATE hlasovani
    SET pro = (
        SELECT COUNT(*)
        FROM hlasovani_poslanec
        WHERE id_hlasovani = p_id_hlasovani AND vysledek = 'A'
    )
    WHERE id_hlasovani = p_id_hlasovani;

    UPDATE hlasovani
    SET proti = (
        SELECT COUNT(*)
        FROM hlasovani_poslanec
        WHERE id_hlasovani = p_id_hlasovani AND vysledek = 'B'
    )
    WHERE id_hlasovani = p_id_hlasovani;
END;

/

DECLARE
    v_pro INT;
    v_proti INT;
BEGIN

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1
    
    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    P_SET_HLASOVANI_POSLANEC(81577, 1942, 'B');
    
    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 112, proti: 2

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
    
    P_SET_HLASOVANI_POSLANEC(81577, 1942, 'A');

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1

    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
END;

-- B2

create or replace FUNCTION F_SET_ZARAZENI_ORG(p_id_osoba INT, p_id_organ INT, p_set CHAR) RETURN CHAR AS
    v_cnt INT;
    v_ret CHAR(1);
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM organ
    WHERE id_organ = p_id_organ;

    IF v_cnt = 0 THEN
        dbms_output.put_line('Neplatne ID organu');
        RETURN 'E';
    END IF;

    SELECT COUNT(*) INTO v_cnt
    FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
        VALUES (p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);

        RETURN 'I';
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
        DELETE FROM zarazeni
        WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

        RETURN 'D';
    ELSE
        RETURN 'N';
    END IF;
END;

/

DECLARE
    v_ret CHAR(1);
BEGIN
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'N');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 1229, 'N');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(6755, 12290, 'Y');
    dbms_output.put_line(v_ret);
END;

