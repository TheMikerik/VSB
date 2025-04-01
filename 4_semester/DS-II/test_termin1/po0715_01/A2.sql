
-- drop table TOO_MANY_ABSENCE_LOG;

CREATE TABLE TOO_MANY_ABSENCE_LOG (
    ID_POSLANEC INTEGER, 
    DEN_OMLUVY DATE, 
    DATUM_PRIDANI TIMESTAMP
);

CREATE OR REPLACE TRIGGER TPreventTooManyAbsence BEFORE INSERT ON OMLUVA FOR EACH ROW
DECLARE
    v_date DATE;
    v_numberOfExcuse INTEGER;
    v_numberOfExcusePerDay INTEGER;
    v_notAllowedException EXCEPTION;
BEGIN
    
    SELECT COUNT(*) INTO v_numberOfExcusePerDay FROM OMLUVA WHERE den=:new.den AND ID_POSLANEC = :new.ID_POSLANEC;

    IF v_numberOfExcusePerDay > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Duplicita');
        RAISE_APPLICATION_ERROR(-1001, 'duplicitni omluva');
    END IF;

    
    SELECT COUNT(*) INTO v_numberOfExcuse
    FROM OMLUVA
    WHERE den BETWEEN ADD_MONTHS(:new.den, -1) AND ADD_MONTHS(:new.den, 1) AND ID_POSLANEC = :new.ID_POSLANEC;

    DBMS_OUTPUT.PUT_LINE('Počet omluv:' || v_numberOfExcuse);

    IF v_numberOfExcuse >= 10 THEN
        INSERT INTO TOO_MANY_ABSENCE_LOG (ID_POSLANEC, DATUM_PRIDANI, DEN_OMLUVY)
        VALUES (:new.ID_POSLANEC, CURRENT_TIMESTAMP, :new.den);

        DBMS_OUTPUT.PUT_LINE('Příliš mnoho omluv (' || v_numberOfExcuse || ').');
    END IF;

END;
