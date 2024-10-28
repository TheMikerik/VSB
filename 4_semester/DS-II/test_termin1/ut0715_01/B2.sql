CREATE OR REPLACE FUNCTION FGetPotentialVoteOutcome(f_idPoslanec INTEGER, f_idHlasovani INTEGER, f_vysledek HLASOVANI.VYSLEDEK%TYPE) RETURN HLASOVANI.VYSLEDEK%TYPE
IS
    v_hlasovani HLASOVANI%ROWTYPE;
    v_vysledek HLASOVANI.VYSLEDEK%TYPE;
    v_kvorum HLASOVANI.KVORUM%TYPE;
    v_hlasuPoslance INTEGER;
    v_alreadyVotedException EXCEPTION;
BEGIN

    SELECT * INTO v_hlasovani FROM HLASOVANI WHERE ID_HLASOVANI = f_idHlasovani;

    SELECT COUNT(*) INTO v_hlasuPoslance FROM HLASOVANI_POSLANEC WHERE ID_HLASOVANI = f_idHlasovani AND ID_POSLANEC = f_idPoslanec;

    IF v_hlasuPoslance > 0 THEN
        RAISE v_alreadyVotedException;
    END IF;

    DBMS_OUTPUT.PUT_LINE('Starý stav hlasování');
    DBMS_OUTPUT.PUT_LINE(v_hlasovani.PRO || ' vs ' || v_hlasovani.PROTI || '; kvorum = ' || v_hlasovani.KVORUM || '; vysledek = ' || v_hlasovani.VYSLEDEK);

    IF f_vysledek = 'A' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.PRO := v_hlasovani.PRO + 1;
    ELSIF f_vysledek = 'B' OR f_vysledek = 'N' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.PROTI := v_hlasovani.PROTI + 1;
    ELSIF f_vysledek = 'C' OR f_vysledek = 'K' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.ZDRZEL := v_hlasovani.ZDRZEL + 1;
    ELSIF f_vysledek = 'F' OR f_vysledek = '@' THEN
        v_hlasovani.PRIHLASENO := v_hlasovani.PRIHLASENO + 1;
        v_hlasovani.NEHLASOVAL := v_hlasovani.NEHLASOVAL + 1;
    END IF;

    v_kvorum := FLOOR(v_hlasovani.PRIHLASENO / 2) + 1;

    IF v_hlasovani.PRO >= v_kvorum THEN
        v_vysledek := 'A';
    ELSE
        v_vysledek := 'R';
    END IF;

    DBMS_OUTPUT.PUT_LINE('Nový stav hlasování');
    DBMS_OUTPUT.PUT_LINE(v_hlasovani.PRO || ' vs ' || v_hlasovani.PROTI || '; kvorum = ' || v_hlasovani.KVORUM || '; vysledek = ' || v_vysledek);

    RETURN v_vysledek;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RETURN NULL;
END;
