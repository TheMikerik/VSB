create or replace TRIGGER TG_INSERT_POSLANEC BEFORE INSERT ON POSLANEC FOR EACH ROW
DECLARE
    v_umrti DATE;
    v_do_organ DATE;
    v_ex EXCEPTION;
BEGIN
    SELECT umrti INTO v_umrti
    FROM osoba
    WHERE id_osoba = :new.id_osoba;

    IF v_umrti IS NOT NULL THEN
        dbms_output.put_line('Dana osoba jiz neni mezi nami.');
        RAISE v_ex;
    END IF;

    SELECT do_organ INTO v_do_organ
    FROM organ
    WHERE id_organ = :new.id_organ;

    IF v_do_organ IS NOT NULL AND v_do_organ < CURRENT_TIMESTAMP THEN
        dbms_output.put_line('Neplatny organ.');
        RAISE v_ex;
    END IF;

    :new.id_kandidatka := -1;

    IF :new.obec = 'Praha' THEN
        :new.id_kraj := 1;
    ELSIF :new.obec = 'Brno' THEN
        :new.id_kraj := 2;
    ELSIF :new.obec = 'Ostrava' THEN
        :new.id_kraj := 3;
    END IF;
END;