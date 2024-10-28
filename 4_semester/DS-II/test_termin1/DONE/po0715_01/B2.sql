-- drop table TOO_MANY_INCLUSION_LOG;

CREATE TABLE TOO_MANY_INCLUSION_LOG (
    ID_OSOBA INTEGER, 
    INFO VARCHAR(300), 
    DATUM_PRIDANI TIMESTAMP
);


CREATE OR REPLACE TRIGGER TPreventTooManyInclusion BEFORE INSERT ON ZARAZENI FOR EACH ROW
DECLARE
    v_date DATE;
    v_osoba OSOBA%ROWTYPE;
    v_numberOfInclusion INTEGER;
    v_info VARCHAR(300);
    v_age INTEGER;
BEGIN
    SELECT COUNT(*) INTO v_numberOfInclusion
    FROM ZARAZENI
    WHERE OD_O < :new.DO_O AND DO_O > :new.OD_O AND ID_OSOBA = :new.ID_OSOBA;

    v_numberOfInclusion := v_numberOfInclusion + 1;

    SELECT * INTO v_osoba FROM OSOBA WHERE ID_OSOBA = :new.ID_OSOBA;

    v_age := FLOOR(MONTHS_BETWEEN(CURRENT_DATE, v_osoba.NAROZENI) / 12);

    v_info := v_osoba.JMENO || ' ' || v_osoba.PRIJMENI ||  ' ' || TO_CHAR(v_age) || ' let - ' || TO_CHAR(v_numberOfInclusion) || ' zařazení';

    IF v_numberOfInclusion > FLOOR(v_age / 10) THEN
        INSERT INTO TOO_MANY_INCLUSION_LOG (ID_OSOBA, INFO, DATUM_PRIDANI) VALUES (:new.ID_OSOBA, v_info, CURRENT_TIMESTAMP);
    END IF;

    DBMS_OUTPUT.PUT_LINE(v_info);

    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('osoba nebyla nalezena');

END;
