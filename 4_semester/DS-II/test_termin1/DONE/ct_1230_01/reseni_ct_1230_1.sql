-- A1
create or replace procedure p_rozdel_funkce(
    p_funkce_od DATE,
    p_funkce_do DATE
) AS
    v_existuje INT;
    v_zarazeni ZARAZENI%rowtype;
    v_cnt_ins INT := 0;
    v_cnt INT;
    ex_CAS_INVALID EXCEPTION ;
BEGIN
    SELECT COUNT(*)
    into v_existuje
    FROM USER_TABLES
    where TABLE_NAME = 'ZARAZENI_FUNKCE';

    IF v_existuje > 0 THEN
        EXECUTE IMMEDIATE 'DROP TABLE ZARAZENI_FUNKCE';
    END IF;

    if p_funkce_od >= p_funkce_do OR (p_funkce_do > CURRENT_DATE) THEN
        raise ex_CAS_INVALID;
    end if;

    execute immediate 'create table ZARAZENI_FUNKCE
        (id_osoba INT REFERENCES OSOBA, id_funkce INT REFERENCES FUNKCE, funkce_od DATE, funkce_do DATE)';

    select count(*) into v_cnt
    FROM ZARAZENI WHERE OD_F >= p_funkce_od AND DO_F <= p_funkce_do AND CL_FUNKCE=1;

    FOR v_zarazeni IN (SELECT * FROM ZARAZENI WHERE OD_F >= p_funkce_od AND DO_F <= p_funkce_do AND CL_FUNKCE=1) LOOP
        EXECUTE IMMEDIATE 'INSERT INTO ZARAZENI_FUNKCE(id_osoba, id_funkce, funkce_od, funkce_do) VALUES (:1, :2, :3, :4)'
        USING v_zarazeni.ID_OSOBA, v_zarazeni.ID_OF, v_zarazeni.OD_F, v_zarazeni.DO_F;
        v_cnt_ins := v_cnt_ins + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Vlozeno ' || v_cnt_ins || ' zaznamu z ' || v_cnt);
exception
    when ex_CAS_INVALID THEN
        DBMS_OUTPUT.PUT_LINE('Spatne zadane parametry p_funkce_od nebo p_funkce_do');
END;

begin
    -- chyba pro spatne casy p_funkce_od a p_funkce_do
    p_rozdel_funkce(to_date('2024-02-01', 'YYYY-MM-DD'), to_date('2022-02-01', 'YYYY-MM-DD'));
    -- OUTPUT: Spatne zadane parametry p_funkce_od nebo p_funkce_do
    -- chyba pro budoucni cas parametru p_funkce_do
    p_rozdel_funkce(to_date('2022-02-01', 'YYYY-MM-DD'), to_date('2025-02-01', 'YYYY-MM-DD'));
    -- OUTPUT: Spatne zadane parametry p_funkce_od nebo p_funkce_do
    -- Spravne volani
    p_rozdel_funkce(to_date('2008-01-01', 'YYYY-MM-DD'), to_date('2022-12-31', 'YYYY-MM-DD'));
    -- OUTPUT: Vlozeno 30 zaznamu z 30
end;


-- A2
create or replace procedure p_poslanec_omluv(
    p_poslanec_id INT,
    p_od OMLUVA.od%TYPE,
    p_do OMLUVA.do%TYPE
) as
    v_poslanec_cnt  int;
    v_hlasovani_cnt int;
    v_omluven_cnt   int;
    v_id_organ      OMLUVA.id_organ%TYPE;

    ex_poslanec EXCEPTION ;
    ex_hlasovani EXCEPTION ;
    ex_omluven EXCEPTION ;
    ex_cas EXCEPTION ;
begin
    select count(*) into v_poslanec_cnt from POSLANEC where ID_POSLANEC = p_poslanec_id;
    select count(*)
    into v_omluven_cnt
    from OMLUVA
    where ID_POSLANEC = p_poslanec_id
      AND to_char(p_od, 'YYYY-MM-DD') = to_char(den, 'YYYY-MM-DD');

    if v_poslanec_cnt <= 0 then
        raise ex_poslanec;
    elsif p_od > p_do then
        raise ex_cas;
    elsif v_omluven_cnt > 0 then
        raise ex_omluven;
    end if;

    select ID_ORGAN into v_id_organ from POSLANEC where ID_POSLANEC = p_poslanec_id;

    insert into OMLUVA(ID_ORGAN, ID_POSLANEC, DEN, OD, DO)
    VALUES (v_id_organ, p_poslanec_id, CAST(p_od AS DATE), p_od, p_do);

    select count(*)
    into v_hlasovani_cnt
    from HLASOVANI
             join HLASOVANI_POSLANEC hp on HLASOVANI.ID_HLASOVANI = hp.ID_HLASOVANI
    where hp.ID_POSLANEC = p_poslanec_id
      AND to_char(p_od, 'YYYY-MM-DD') = to_char(datum, 'YYYY-MM-DD')
      and to_char(cas, 'HH24:MI:SS') between to_char(p_od, 'HH24:MI:SS') and to_char(p_do, 'HH24:MI:SS');
    if v_hlasovani_cnt > 0 THEN
        raise ex_hlasovani;
    end if;

    commit;
    DBMS_OUTPUT.PUT_LINE('Omluva zaznamenana.');
exception
    when ex_poslanec then
        DBMS_OUTPUT.PUT_LINE('Poslanec neexistuje!');
    when ex_omluven then
        DBMS_OUTPUT.PUT_LINE('Poslanec je jiz omluven!');
    when ex_cas then
        DBMS_OUTPUT.PUT_LINE('Hodnota DO je mensi nez hodnota OD');
    when ex_hlasovani then
        DBMS_OUTPUT.PUT_LINE('Poslanec ma v dane dobe hlasovani a nemuze byt omluven');
        rollback;
end;


declare
    v_od TIMESTAMP := to_timestamp('2024-03-01 09:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do TIMESTAMP := to_timestamp('2024-03-01 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
begin
    -- chyba pro neexistujiciho poslance
    p_poslanec_omluv(2050, v_od, v_do);
    -- OUTPUT: Poslanec neexistuje!
    v_do := to_timestamp('2024-03-01 09:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_od := to_timestamp('2024-03-01 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba pro spatne casy
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Hodnota DO je mensi nez hodnota OD
    v_od := to_timestamp('2023-09-15 13:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do := to_timestamp('2023-09-15 14:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba - poslanec uz je omluveny
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Poslanec je jiz omluven!
    v_od := to_timestamp('2023-09-26 13:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do := to_timestamp('2023-09-26 15:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba - poslanec v te dobe hlasoval
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Poslanec ma v dane dobe hlasovani a nemuze byt omluven
    v_od := to_timestamp('2024-01-01 13:00:00', 'YYYY-MM-DD HH24:MI:SS');
    v_do := to_timestamp('2024-01-01 15:00:00', 'YYYY-MM-DD HH24:MI:SS');
    p_poslanec_omluv(1940, v_od, v_do);
    -- OUTPUT: Omluva zaznamenana.
end;


-- B1
create or replace procedure p_rozdel_organ(
    p_organ_od DATE,
    p_organ_do DATE
) AS
    v_existuje INT;
    v_zarazeni ZARAZENI%rowtype;
    v_cnt_ins INT := 0;
    v_cnt INT;
    ex_CAS_INVALID EXCEPTION ;
BEGIN
    SELECT COUNT(*)
    into v_existuje
    FROM USER_TABLES
    where TABLE_NAME = 'ZARAZENI_ORGAN';

    IF v_existuje > 0 THEN
        EXECUTE IMMEDIATE 'DROP TABLE ZARAZENI_ORGAN';
    END IF;

    if p_organ_od >= p_organ_do OR (p_organ_do > CURRENT_DATE) THEN
        raise ex_CAS_INVALID;
    end if;

    execute immediate 'create table ZARAZENI_ORGAN
        (id_osoba INT REFERENCES OSOBA, id_organ INT REFERENCES ORGAN, organ_od DATE, organ_do DATE)';

    select count(*) into v_cnt
    FROM ZARAZENI WHERE OD_F >= p_organ_od AND DO_F <= p_organ_do AND CL_FUNKCE=0;

    FOR v_zarazeni IN (SELECT * FROM ZARAZENI WHERE OD_F >= p_organ_od AND DO_F <= p_organ_do AND CL_FUNKCE=0) LOOP
        EXECUTE IMMEDIATE 'INSERT INTO ZARAZENI_ORGAN(id_osoba, ID_ORGAN, organ_od, organ_do) VALUES (:1, :2, :3, :4)'
        USING v_zarazeni.ID_OSOBA, v_zarazeni.ID_OF, v_zarazeni.OD_F, v_zarazeni.DO_F;
        v_cnt_ins := v_cnt_ins + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Vlozeno ' || v_cnt_ins || ' zaznamu z ' || v_cnt);
exception
    when ex_CAS_INVALID THEN
        DBMS_OUTPUT.PUT_LINE('Spatne zadane parametry p_organ_od nebo p_organ_do');
END;



-- B2
create or replace procedure p_poslanec_hlasuj(
    p_poslanec_id HLASOVANI_POSLANEC.ID_POSLANEC%TYPE,
    p_hlasovani_id HLASOVANI_POSLANEC.ID_HLASOVANI%TYPE,
    p_cas HLASOVANI.CAS%TYPE,
    p_vysledek HLASOVANI_POSLANEC.VYSLEDEK%TYPE
) as
    v_poslanec_cnt  int;
    v_hlasovani_cnt int;
    v_omluven       INT;

    ex_poslanec EXCEPTION ;
    ex_hlasovani EXCEPTION ;
    ex_cas EXCEPTION ;
    ex_vysledek EXCEPTION ;
    ex_omluven EXCEPTION ;
begin
    select count(*) into v_poslanec_cnt from POSLANEC where ID_POSLANEC = p_poslanec_id;
    select count(*)
    into v_hlasovani_cnt
    from HLASOVANI
    where ID_HLASOVANI = p_hlasovani_id;

    if v_poslanec_cnt <= 0 then
        raise ex_poslanec;
    elsif v_hlasovani_cnt <= 0 then
        raise ex_hlasovani;
    elsif p_vysledek NOT IN ('A', 'B', 'X') then
        raise ex_vysledek;
    elsif p_cas > CURRENT_TIMESTAMP THEN
        raise ex_cas;
    end if;

    select count(*)
    into v_omluven
    from OMLUVA
    where ID_POSLANEC = p_poslanec_id
      and to_char(den, 'YYYY-MM-DD') = to_char(p_cas, 'YYYY-MM-DD')
      and to_char(p_cas, 'HH24:MI:SS') between to_char(od, 'HH24:MI:SS') and to_char(do, 'HH24:MI:SS');

    if v_omluven > 0 then
        raise ex_omluven;
    end if;

    delete from HLASOVANI_POSLANEC
    where ID_HLASOVANI=p_hlasovani_id and ID_POSLANEC=p_poslanec_id;

    insert into HLASOVANI_POSLANEC(ID_POSLANEC, ID_HLASOVANI, VYSLEDEK)
    VALUES (p_poslanec_id, p_hlasovani_id, p_vysledek);

    update HLASOVANI
    set PRO = PRO + CASE WHEN p_vysledek = 'A' THEN 1 else 0 END,
        PROTI=PROTI + CASE WHEN p_vysledek = 'B' THEN 1 else 0 END,
        ZDRZEL=ZDRZEL + CASE WHEN p_vysledek = 'X' THEN 1 else 0 END
    where ID_HLASOVANI = p_hlasovani_id;
    DBMS_OUTPUT.PUT_LINE('Hlasování bylo zaznamenáno.');
    commit;
exception
    when ex_poslanec then
        DBMS_OUTPUT.PUT_LINE('Poslanec neexistuje!');
    when ex_hlasovani then
        DBMS_OUTPUT.PUT_LINE('Hlasování neexistujte');
    when ex_vysledek then
        DBMS_OUTPUT.PUT_LINE('Výsledek nemá platnou hodnotu');
    when ex_cas then
        DBMS_OUTPUT.PUT_LINE('Čas hlasování je v budoucnosti!');
    when ex_omluven then
        DBMS_OUTPUT.PUT_LINE('Poslanec je na dané hlasování omluven!');
        rollback;
end;

declare
    v_cas TIMESTAMP := to_timestamp('2023-09-06 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
begin
    -- chyba pro neexistujiciho poslance
    p_poslanec_hlasuj(2050, 81531, v_cas, 'X');
    -- OUTPUT: Poslanec neexistuje!
    -- chyba pro neexistujici hlasovani
    p_poslanec_hlasuj(1940, 100000, v_cas, 'B');
    -- OUTPUT: Hlasování neexistujte
    -- chyba - spatny vysledek
    p_poslanec_hlasuj(1940, 81531, v_cas, 'Z');
    -- OUTPUT: Výsledek nemá platnou hodnotu
    -- chyba - poslanec je v dany cas omluven
    p_poslanec_hlasuj(1940, 81531, v_cas, 'A');
    -- OUTPUT: Poslanec je na dané hlasování omluven!
    v_cas := to_timestamp('2025-09-06 16:00:00', 'YYYY-MM-DD HH24:MI:SS');
    -- chyba - hlasovani v budoucnu
    p_poslanec_hlasuj(1940, 81531, v_cas, 'A');
    -- OUTPUT: Čas hlasování je v budoucnosti!
    v_cas := to_timestamp('2023-09-26 14:18:00', 'YYYY-MM-DD HH24:MI:SS');
    p_poslanec_hlasuj(1940, 81531, v_cas, 'A');
    -- OUTPUT: Hlasování bylo zaznamenáno.
end;

