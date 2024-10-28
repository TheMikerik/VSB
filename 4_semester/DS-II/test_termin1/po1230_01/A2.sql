CREATE OR REPLACE TRIGGER TUmrti BEFORE UPDATE ON Osoba FOR EACH ROW
DECLARE
    v_hlasovaniCount INTEGER;
    v_idPoslanec INTEGER;
    v_invalidUmrtiException EXCEPTION;
BEGIN

    IF :new.umrti IS NOT NULL THEN

        SELECT COUNT(*) INTO v_hlasovaniCount FROM Hlasovani h
            INNER JOIN Hlasovani_poslanec hp 
                ON h.id_hlasovani = hp.id_hlasovani 
            INNER JOIN Poslanec p 
                ON p.id_poslanec = hp.id_poslanec 
            WHERE p.id_osoba = :new.id_osoba AND h.datum > :new.umrti;

        IF v_hlasovaniCount > 0 THEN
            DBMS_OUTPUT.PUT_LINE('Špatné datum úmrtí -> poslanec nemohl hlasovat po smrti.');
            RAISE v_invalidUmrtiException;
        END IF;

        DELETE FROM Omluva WHERE OD > :new.umrti AND id_poslanec IN (SELECT id_poslanec FROM Poslanec WHERE id_osoba = :new.id_osoba);
        
        DBMS_OUTPUT.PUT_LINE('Počet odstraněných řádků:' || SQL%ROWCOUNT); -- případně select počtu před delete

    END IF;

END;
