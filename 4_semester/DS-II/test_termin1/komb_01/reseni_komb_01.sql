-- A1
ALTER TABLE poslanec
ADD absence_level CHAR(1) DEFAULT 'x' CHECK (absence_level IN ('L', 'M', 'H', 'x'));

CREATE OR REPLACE PROCEDURE SetAbsenceLevel(p_od DATE, p_do DATE) IS
BEGIN
    FOR rec IN (SELECT id_poslanec, COUNT(*) AS pocet_absenci
                FROM omluva
                WHERE den BETWEEN p_od AND p_do
                GROUP BY id_poslanec) LOOP
        UPDATE poslanec
        SET absence_level =
            CASE
                WHEN rec.pocet_absenci < 10 THEN 'L'
                WHEN rec.pocet_absenci BETWEEN 11 AND 20 THEN 'M'
                ELSE 'H'
            END
        WHERE id_poslanec = rec.id_poslanec;
    END LOOP;
    COMMIT;
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
END;

-----------------------------------------------------------------------

-- A2
CREATE OR REPLACE FUNCTION GetConfusedVote(p_id_osoba IN NUMBER) 
RETURN INT IS
    v_pocet_zmatecnych_hlasovani int;
    v_pocet_osob int;
BEGIN
    SELECT COUNT(*) INTO v_pocet_osob
    FROM osoba
    WHERE id_osoba = p_id_osoba;

    IF v_pocet_osob = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Osoba s daným ID neexistuje.');
        RETURN -1;
    END IF;

    -- Spočítání zmatecných hlasování dané osoby v daném roce
    SELECT COUNT(*)
    INTO v_pocet_zmatecnych_hlasovani
    FROM zmatecne_hlasovani_poslanec 
    JOIN hlasovani on zmatecne_hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani
    WHERE id_osoba = p_id_osoba AND 
      EXTRACT(YEAR FROM datum) = EXTRACT(YEAR FROM CURRENT_TIMESTAMP);

    COMMIT;
    RETURN v_pocet_zmatecnych_hlasovani;
EXCEPTION
   WHEN OTHERS THEN
      ROLLBACK;
END;