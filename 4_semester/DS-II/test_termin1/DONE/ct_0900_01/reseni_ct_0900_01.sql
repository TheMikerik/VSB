-- A1

create or replace TRIGGER TG_ZARAZENI BEFORE INSERT OR UPDATE ON zarazeni FOR EACH ROW
DECLARE
    v_cnt INT;
    v_ex EXCEPTION;
BEGIN
    IF :new.cl_funkce = 0 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM organ
        WHERE id_organ = :new.id_of;

        IF v_cnt = 0 THEN
            dbms_output.put_line('Invalid id_organ.');
            RAISE v_ex;
        END IF;
    ELSIF :new.cl_funkce = 1 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM funkce
        WHERE id_funkce = :new.id_of;

        IF v_cnt = 0 THEN
            dbms_output.put_line('Invalid id_funkce.');
            RAISE v_ex;
        END IF;    
    ELSE
        dbms_output.put_line('Invalid cl_funkce.');
        RAISE v_ex;
    END IF;

    -- Pripadne elegantnejsi reseni by bylo raise_application_error( -20001, 'This is a custom error' );.
END;

/

-- Priklad vlozeni OK:
INSERT INTO Zarazeni(id_osoba, id_of, cl_funkce, od_o)
VALUES (6755, 1229, 0, CURRENT_TIMESTAMP);

-- Priklad neplatne ID funkce.
INSERT INTO Zarazeni(id_osoba, id_of, cl_funkce, od_o)
VALUES (6755, 1229, 1, CURRENT_TIMESTAMP);

-- Priklad neplatne cl_funkce.
INSERT INTO Zarazeni(id_osoba, id_of, cl_funkce, od_o)
VALUES (6755, 1229, 2, CURRENT_TIMESTAMP);

-- A2


create or replace PROCEDURE P_PRINT_HLASOVANI(p_id_hlasovani INT) AS
    v_prev_vysledek CHAR(1) := ' ';
BEGIN
    FOR v_rec IN (
        SELECT hp.vysledek, o.jmeno, o.prijmeni
        FROM
            hlasovani_poslanec hp
            JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
            JOIN osoba o ON p.id_osoba = o.id_osoba
        WHERE hp.id_hlasovani = p_id_hlasovani
        ORDER BY hp.vysledek) LOOP

        IF v_rec.vysledek != v_prev_vysledek THEN
            dbms_output.put_line('vysledek ' || v_rec.vysledek || ':');
            v_prev_vysledek := v_rec.vysledek;
        END IF;

        dbms_output.put_line('  * ' || v_rec.jmeno || ' ' || v_rec.prijmeni);
    END LOOP;
END;

/

BEGIN
    P_PRINT_HLASOVANI(29714);
END;

-- B1

create or replace PROCEDURE P_SET_ZARAZENI_FCE(p_id_osoba INT, p_id_funkce INT, p_set CHAR) AS
    v_cnt INT;
    v_ex EXCEPTION;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM funkce
    WHERE id_funkce = p_id_funkce;

    IF v_cnt = 0 THEN
        dbms_output.put_line('Neplatne ID funkce');
        RAISE v_ex;
    END IF;

    SELECT COUNT(*) INTO v_cnt
    FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_funkce AND cl_funkce = 1;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
        VALUES (p_id_osoba, p_id_funkce, 1, CURRENT_TIMESTAMP);

        dbms_output.put_line('Nastaveno zarazeni osoby do funke.');
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
        DELETE FROM zarazeni
        WHERE id_osoba = p_id_osoba AND id_of = p_id_funkce AND cl_funkce = 1;

        dbms_output.put_line('Zruseno zarazeni osoby z funke.');
    ELSE
        dbms_output.put_line('Nebyla provedena zadna operace.');
    END IF;

END;

/

BEGIN
    P_SET_ZARAZENI_FCE(6755, 2930, 'Y');
    P_SET_ZARAZENI_FCE(6755, 2930, 'Y');
    P_SET_ZARAZENI_FCE(6755, 2930, 'N');
    P_SET_ZARAZENI_FCE(6755, 2930, 'N');
END;

-- B2

create or replace FUNCTION F_COPY_SCHUZE(p_id_schuze INT, p_od_schuze DATE, p_do_schuze DATE) RETURN INT AS
    v_id_organ INT;
    v_id_schuze_new INT;
    v_schuze_new INT;
BEGIN
    SELECT id_organ INTO v_id_organ
    FROM schuze
    WHERE id_schuze = p_id_schuze;

    SELECT COALESCE(MAX(id_schuze), 0) + 1 INTO v_id_schuze_new
    FROM schuze;

    SELECT COALESCE(MAX(schuze), 0) + 1 INTO v_schuze_new
    FROM schuze
    WHERE id_organ = v_id_organ;

    INSERT INTO schuze (id_schuze, id_organ, schuze, od_schuze, do_schuze, aktualizace)
    SELECT v_id_schuze_new, id_organ, v_schuze_new, p_od_schuze, p_do_schuze, aktualizace
    FROM schuze
    WHERE id_schuze = p_id_schuze;

    INSERT INTO bod_schuze (id_bod, id_schuze, id_tisk, id_typ, bod, uplny_naz, uplny_kon, poznamka, id_bod_stav, pozvanka, rj, pozn2, druh_bodu, id_sd, zkratka)
    SELECT id_bod, v_id_schuze_new, id_tisk, id_typ, bod, uplny_naz || ' (kopie)', uplny_kon, poznamka, id_bod_stav, pozvanka, rj, pozn2, druh_bodu, id_sd, zkratka
    FROM bod_schuze
    WHERE id_schuze = p_id_schuze;

    RETURN v_id_schuze_new;
END;

/

DECLARE
    v_id_schuze_new INT;
    v_pocet_bodu INT;
BEGIN
    v_id_schuze_new := F_COPY_SCHUZE(734, TO_DATE('2024-03-28', 'yyyy-mm-dd'), TO_DATE('2024-03-29', 'yyyy-mm-dd'));
    dbms_output.put_line('ID nove schuze: ' || TO_CHAR(v_id_schuze_new));
    
    SELECT COUNT(*) INTO v_pocet_bodu
    FROM bod_schuze
    WHERE id_schuze = v_id_schuze_new;
    
    dbms_output.put_line('Pocet zkopirovaych bodu: ' || TO_CHAR(v_pocet_bodu));
END;