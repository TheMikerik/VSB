--zadani cviceni --hlasovani a(pro), b(proti), x(zdrzel)

--1. napiste trigger, ktery pri vlozeni nebo aktualizaci zaznamu v tabulce hlasovani_poslanec upravi statistiky v tabulce hlasovani
create or replace trigger  hlas_posl
after insert or update
on hlasovani_poslanec
for each row
begin
    case
        when inserting then
            update hlasovani set
                pro=pro + CASE when :new.vysledek='A' then 1 else 0 end,
                proti=proti + CASE when :new.vysledek='B' then 1 else 0 end,
                zdrzel=zdrzel + CASE when :new.vysledek='X' then 1 else 0 end
            where hlasovani.id_hlasovani = :new.id_hlasovani;
        when updating('vysledek') then
            IF :old.vysledek <> :new.vysledek THEN
                update hlasovani set
                    pro=pro + CASE when :new.vysledek='A' then 1 else 0 end - CASE when :old.vysledek='A' then 1 else 0 end,
                    proti=proti + CASE when :new.vysledek='B' then 1 else 0 end - CASE when :old.vysledek='B' then 1 else 0 end,
                    zdrzel=zdrzel + CASE when :new.vysledek='X' then 1 else 0 end  - CASE when :old.vysledek='X' then 1 else 0 end
            where hlasovani.id_hlasovani = :old.id_hlasovani;
            END IF;
           
    end case;
end;


--2. napiste proceduru zarad_osobu_do s parametry (id_osoba int, typ funkce | organ, id_of int).
--procedura zkontroluje, zda existuji zaznamy pro osobu a organ/funkci a vlozi zaznam do tabulky zarazeni.

create or replace procedure zarad_osobu_do (p_id_osoba osoba.id_osoba%TYPE, p_type VARCHAR2, p_id_of zarazeni.id_of%TYPE)
as
    v_cnt int;
    ex_404 exception;
    ex_invalid_type exception;
begin
    select count(*) into v_cnt from osoba where osoba.id_osoba = p_id_osoba;
    if v_cnt <= 0 THEN
        raise ex_404;
    end if;
   
    if p_type = 'organ' then
        select count(*) into v_cnt from organ where organ.id_organ = p_id_of;
    elsif p_type = 'funkce' then  
        select count(*) into v_cnt from funkce where funkce.id_funkce= p_id_of;
    else
        raise ex_invalid_type;
    end if;
   
    if v_cnt <= 0 then
        raise ex_404;
    end if;
   
    if p_type = 'organ' then
        insert into zarazeni(id_osoba, cl_funkce, id_of, od_o)
        values (p_id_osoba, 0, p_id_of, CURRENT_DATE);
    else
        insert into zarazeni(id_osoba, cl_funkce, id_of, od_f)
        values (p_id_osoba, 1, p_id_of, CURRENT_DATE);
    end if;
end;



--3. napiste ulozenou funkci poslanci_strana s parametry(zkratka varchar2) vypise vsechny poslance z daneho organu (pouzijte kurzor).
--Funkce bude vracet pocet poslancu. Funkce musi zkontrolovat, ze strana existuje
create or replace function poslanci_strana (p_zkratka VARCHAR2)
return INT
as
    v_cnt_pos number := 0;
begin
    for cv_osoba IN (
        select distinct o.*
        from organ
        join zarazeni z on z.id_of = organ.id_organ and z.cl_funkce = 0
        join osoba o on z.id_osoba = o.id_osoba
        join poslanec p on p.id_osoba = o.id_osoba
        where zkratka = p_zkratka
    ) LOOP
        v_cnt_pos := v_cnt_pos + 1;
        pprint(cv_osoba.jmeno || ' ' || cv_osoba.prijmeni);
    end loop;
   
    return v_cnt_pos;
   
    exception
        when NO_DATA_FOUND then
            pprint('Strana neexistuje!');
   
end;

execute pprint('Pocet poslancu: ' || poslanci_strana('ODS'));


























create or replace trigger UpdateHlasovani
after update or insert on hlasovani_poslanec
for each row

begin
    case
        when inserting then
            if :new.vysledek = 'A' then
                update hlasovani set pro = pro + 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
            elsif :new.vysledek = 'B' then
                update hlasovani set proti = proti + 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
            else
                update hlasovani set zdrzel = zdrzel + 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
            end if;

        when updating then
            if :new.vysledek = 'A' then
                if :old.vysledek = 'B' then
                    update hlasovani set pro = pro + 1, proti = proti - 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
                elsif :old.vysledek = 'X' then
                    update hlasovani set pro = pro + 1, zdrzel = zdrzel - 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
                end if;
            elsif :new.vysledek = 'B' then
                if :old.vysledek = 'A' then
                    update hlasovani set pro = pro - 1, proti = proti + 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
                elsif :old.vysledek = 'X' then
                    update hlasovani set proti = proti + 1, zdrzel = zdrzel - 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
                end if;
            else
                if :old.vysledek = 'A' then
                    update hlasovani set pro = pro - 1, zdrzel = zdrzel + 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
                elsif :old.vysledek = 'B' then
                    update hlasovani set proti = proti - 1, zdrzel = zdrzel + 1 where hlasovani.id_hlasovani = :new.id_hlasovani;
                end if;
            end if;

    end case;

end;

-- Napiste proceduru zkontroluje zda existuji zaznamy osoby a organu a vlozi zaznam do tabulky zarazeni

create or replace procedure zarad_osobu_do(p_id_osoba Osoba.id_osoba%type,
                                           p_typ Varchar2,
                                           p_id_of zarazeni.id_of%type)
as
    v_cnt INT;
    does_not_exists Exception;
begin
    if p_typ = 'organ' then
        select count(*) into v_cnt from osoba where osoba.id_osoba = p_id_osoba;
        if v_cnt > 0 then
            v_cnt := 0;
            select count(*) into v_cnt from organ where organ.id_organ = p_id_of;
            if v_cnt > 0 then
                insert into zarazeni (id_osoba, id_of, cl_funkce, od_o, do_o, od_f, do_f) values (p_id_osoba, p_id_of, 0, CURRENT_DATE, null, null, null);
            else
                raise does_not_exists;
            end if;
        else
            raise does_not_exists;
        end if;

    elsif p_typ = 'funkce' then
         select count(*) into v_cnt from osoba where osoba.id_osoba = p_id_osoba;
        if v_cnt > 0 then
            v_cnt := 0;
            select count(*) into v_cnt from funkce where funkce.id_funkce = p_id_of;
            if v_cnt > 0 then
                insert into zarazeni (id_osoba, id_of, cl_funkce, od_o, do_o, od_f, do_f) values (p_id_osoba, p_id_of, 1, CURRENT_DATE, null, null, null);
            else
                raise does_not_exists;
            end if;
        else
            raise does_not_exists;
        end if;

    else
        PPrint('Å patny typ');

    end if;

    exception
        when does_not_exists then
            PPRINT('Neexistuje zaznam');

end;

begin
    zarad_osobu_do(144, 'organ', 34);
end;


create or replace function poslanci_strana(p_zkratka Varchar2)
return INT
as
  v_cnt INT;
  not_found Exception;

begin
    select count(*) into v_cnt from organ where organ.zkratka = p_zkratka;
    if v_cnt > 0 then
        for c_poslanec in (select pl.* 
        from organ o
        join zarazeni z on z.id_of = o.id_organ and z.cl_funkce = 0
        join osoba os on os.id_osoba = z.id_osoba
        join poslanec pl on pl.id_osoba = os.id_osoba
        where o.zkratka = p_zkratka)
        loop
            PPrint(c_poslanec.id_poslanec || ' ' ||  c_poslanec.id_osoba);

        end loop;

        select count(*) into v_cnt from organ o
        join zarazeni z on z.id_of = o.id_organ and z.cl_funkce = 0
        join osoba os on os.id_osoba = z.id_osoba
        join poslanec pl on pl.id_osoba = os.id_osoba
        where o.zkratka = p_zkratka;
        return v_cnt;

    else
        raise not_found;

    end if;

    exception
        when not_found then
            pprint('Organ se zkratkou nebyl nalezen');
            return 0;

end;