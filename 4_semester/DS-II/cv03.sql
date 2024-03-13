CREATE OR REPLACE PROCEDURE PPrint(p_text VARCHAR2) AS
BEGIN
    dbms_output.put_line(p_text);
END;


CREATE OR REPLACE PROCEDURE PAddStudent1(
    p_login Student.login%TYPE,
    p_fname Student.fname%TYPE,
    p_lname Student.lname%TYPE,
    p_email Student.email%TYPE,
    p_grade Student.grade%TYPE,
    p_dateOfBirth Student.date_of_birth%TYPE
) AS
BEGIN
    insert into Student (login, fname, lname, email, grade, date_of_birth)
    values (p_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;




CREATE OR REPLACE PROCEDURE PAddStudent2(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) AS
    
    v_login Student.login%TYPE;
BEGIN
    v_login := LOWER(SUBSTR(p_lname, 1, 3)) || '000';
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;





CREATE OR REPLACE PROCEDURE PAddStudent3(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) AS
    
    v_studentCount INT;
    v_login Student.login%TYPE;
BEGIN
    SELECT COUNT(*) + 1 INTO v_studentCount
    FROM Student;

    v_login := LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_studentCount, 3, '0');
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;



CREATE OR REPLACE FUNCTION FAddStudent2(
    p_login IN Student.login%TYPE,
    p_fname IN Student.fname%TYPE,
    p_lname IN Student.lname%TYPE,
    p_email IN Student.email%TYPE,
    p_grade IN Student.grade%TYPE,
    p_dateOfBirth IN Student.date_of_birth%TYPE
) RETURN VARCHAR2 IS
    v_result VARCHAR2(3);
BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (p_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    v_result := 'OK';
    RETURN v_result;
EXCEPTION
    WHEN OTHERS THEN
        v_result := 'error';
        RETURN v_result;
END;






CREATE OR REPLACE FUNCTION FAddStudent2(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS
    
    v_studentCount INT;
    v_login Student.login%TYPE;
BEGIN
    SELECT COUNT(*) + 1 INTO v_studentCount
    FROM Student;

    v_login := LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_studentCount, 3, '0');
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
    
    RETURN v_login;
    
EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;







CREATE OR REPLACE FUNCTION FAddStudent3(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS
    
    v_login Student.login%TYPE;
BEGIN
    v_login := FGetLogin(p_lname);
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    RETURN v_login;
    
EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;
