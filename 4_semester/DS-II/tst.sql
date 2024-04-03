-- Napiste trigger, ktery bude spusteny pred pridanim zaznamu do tabulky POSLANEC. Trigger overi, zda je vlkadana osoba
-- ziva. Nasledne zkontroluje, zda je organ stale aktivni (aktualni datum je mensi nez do_organ, pripadne do_organe neni
-- vyplneno). Pokud nektera z podminek neni splanena, dojde k vypisu chybove hlasky a vyvolani vyjimky. Trigger dale
-- nastavi id_kandidatky na -1 a id_kraje podle obce a nasledovne

create or replace trigger tg_insert_poslanec before insert on POSLANEC for each row
declare
    v_umrti date;
    v_do_organ date;
    v_ex exception;
begin
    select umrti into v_umrti
    from osoba
        where id_osoba =: new.id_osoba;

    if v_umrti is not null then
        dbms_output.put_line('Dana osoba je jiz mrtva');
    end if;

    select do_organ into v_do_organ
    from organ
    where id_organ =: new.id_organ;

    if v_do_organ is not null and v_do_organ < current_timestamp then
        dbms_output.put_line('Dany organ jiz neni platny');
        raise v_ex;
    end if;
end;





-- Napište proceduru P_ZMATECNE_HLASOVANI, která v tabulce HLASOVANI vytvoří atribut zmatecne_hlasovani typu CHAR(1)
-- Atribut bude vytvořen pouze, pokud zatím neexistuje. Následně procedura aktualizuje tento atribut na hodnotu 1 u
-- všech hlasování, která jsou označená jako zmatečná (ID hlasování je uvedeno v tab. ZMATECNE). U ostatních hlasování
-- bude nový atribut nastaven na 0. Nakonec procedura tabulku ZMATECNE odstraní.

CREATE PROCEDURE P_ZMATECNE_HLASOVANI
AS
BEGIN
    BEGIN
        ALTER TABLE HLASOVANI
        ADD zmatecne_hlasovani CHAR(1);
    END;

    UPDATE HLASOVANI
    SET zmatecne_hlasovani = '1'
    WHERE ID_hlasovani IN (SELECT ID_hlasovani FROM ZMATECNE);

    UPDATE HLASOVANI
    SET zmatecne_hlasovani = '0'
    WHERE zmatecne_hlasovani IS NULL;

    DROP TABLE IF EXISTS ZMATECNE;
END;