------------------------------------------------------------------------------------------------------------ 1

-- 2.1. Vypište kódy a názvy kurzů, které vyučuje Jerry Jordon. 
SELECT Course.Code, Course.Name
FROM
    Course
    JOIN Teacher ON Course.teacher_login = Teacher.login
WHERE Teacher.fname = 'Jerry' AND Teacher.lname = 'Jordon';

-- 2.2. Vypište studenty, které v roce 2020 nebo 2021 učil Jerry Jordon.
SELECT DISTINCT Student.fname, Student.lname
FROM
    Student
    JOIN StudentCourse ON Student.login = StudentCourse.student_login
    JOIN Course ON StudentCourse.course_code = Course.code
    JOIN Teacher ON Course.teacher_login = Teacher.login
WHERE
    StudentCourse.year IN (2020, 2021) AND Teacher.fname = 'Jerry' AND Teacher.lname = 'Jordon';
    

-- 2.3. Pro všechny studenty v doméně @vsb.cz vypište počet zapsaných kurzů.
SELECT Student.fname, Student.lname, COUNT(StudentCourse.course_code) AS cnt
FROM
    Student
    LEFT JOIN StudentCourse ON Student.login = StudentCourse.student_login
WHERE Student.email LIKE '%vsb.cz'
GROUP BY Student.login, Student.fname, Student.lname;

-- 2.4. Pro všechny studenty vypište, kolik je v roce 2020 učilo různých učitelů.
SELECT Student.fname, Student.lname, COUNT(DISTINCT Course.teacher_login) AS cnt
FROM
    Student
    LEFT JOIN StudentCourse ON Student.login = StudentCourse.student_login AND StudentCourse.year = 2020
    LEFT JOIN Course ON StudentCourse.course_code = Course.code
GROUP BY Student.login, Student.fname, Student.lname;

-- 2.5. Pro každého učitele (jméno a příjmení) vypište kurz(y) s nejvyšší kapacitou, kapacita bude součástí výsledku. Učitele bez kurzů nevypisujte.
SELECT Teacher.fname, Teacher.lname, c1.name, c1.capacity
FROM
    Teacher
    JOIN Course c1 ON Teacher.login = c1.teacher_login
WHERE c1.capacity >= ALL (
    SELECT c2.capacity
    FROM Course c2
    WHERE c1.teacher_login = c2.teacher_login);

-- 2.6. Vypište učitele (jméno a příjmení), kteří vyučují největší počet kurzů.
WITH T AS
(
    SELECT Teacher.fname, Teacher.lname, COUNT(Course.code) AS cnt
    FROM
        Teacher
        LEFT JOIN Course ON Teacher.login = Course.teacher_login
    GROUP BY Teacher.login, Teacher.fname, Teacher.lname
)
SELECT *
FROM T
WHERE cnt >= ALL (SELECT cnt FROM T);

-- 2.7. Vypište studenty, které v roce 2020 nevyučoval Jerry Jordon, ale zároveň tito studenti měli v tomto roce zapsán alespoň jeden kurz.
SELECT fname, lname
FROM Student
WHERE login NOT IN (
    SELECT StudentCourse.student_login
    FROM    
        StudentCourse
        JOIN Course ON StudentCourse.course_code = Course.code
        JOIN Teacher ON Course.teacher_login = Teacher.login
    WHERE Teacher.fname = 'Jerry' AND Teacher.lname = 'Jordon' AND StudentCourse.year = 2020
) AND login IN
(
    SELECT student_login
    FROM StudentCourse
    WHERE year = 2020
);

-- 2.8. Pro každý kurz vypište průměrný počet studentů, kteří měli daný kurz zapsán v jednotlivých letech.
-- Uvažujte jen kurzy, na které byl či je zapsán alespoň jeden student.
SELECT code, name, AVG(cnt) AS average
FROM
(
    SELECT Course.code, Course.name, COUNT(StudentCourse.student_login) AS cnt
    FROM
        Course
        JOIN StudentCourse ON Course.code = StudentCourse.course_code
    GROUP BY Course.code, Course.name, StudentCourse.year
) T
GROUP BY code, name

-- 3.1. Přidejte do tabulky Teacher učitele Peter Burton s loginem bur154 a katedrou Department of Mathematic.
INSERT INTO Teacher(login, fname, lname, department) VALUES ('bur154', 'Peter', 'Burton', 'Department of Mathematic');
 
-- 3.2. Nastavte kurzu Database Systems II nově vloženého učitele bur154.
UPDATE Course set teacher_login = 'bur154' where name = 'Database Systems II';

-- 3.3. Zrušte jedním SQL příkazem zápis kurzů (tj., záznamy v tab. StudentCourse), které vyučuje Carl Artis.
DELETE FROM StudentCourse
WHERE course_code IN (
    SELECT code
    FROM Course JOIN Teacher ON Course.teacher_login = Teacher.login
    WHERE fname = 'Carl' AND lname = 'Artis'
);
												
-- 3.4. Nastavte v databázi studentovi Barbara Jones účast pro rok 2021 na všech kurzech, které vyučuje Walter Perryman.
INSERT INTO StudentCourse
(
    year,
    student_login,
    course_code
)
SELECT 2021,
    (
        SELECT login
        FROM Student
        WHERE fname = 'Barbara' AND lname = 'Jones'
    ),
    Course.code
FROM Course JOIN Teacher ON Course.teacher_login = Teacher.login
WHERE Teacher.fname = 'Walter' AND Teacher.lname = 'Perryman';


-- 4.1. Nastavte studentovi 'smi324' datum narození na 2.3.1997.
UPDATE Student
SET date_of_birth = TO_DATE('1997-03-02', 'YYYY-MM-DD')
WHERE login = 'smi324';

-- 4.2. Pro každého studenta vypište jeho věk.
SELECT fname, lname, FLOOR(MONTHS_BETWEEN(current_timestamp, date_of_birth) / 12)
FROM Student

-- 4.3. Ke každému studentovi vypište datum, kdy oslavil své 18-té narozeniny.
SELECT fname, lname, ADD_MONTHS(date_of_birth, 18 * 12) AS age18
FROM Student

-- 4.4. Vypište ke každému studentovi v samostatných sloupcích rok, měsíc a den jeho narození.
SELECT
    fname, lname,
    EXTRACT(YEAR FROM date_of_birth) AS year,
    EXTRACT(MONTH FROM date_of_birth) AS month,
    EXTRACT(DAY FROM date_of_birth) AS day
FROM Student

-- 4.5. Vypište studenty, kteří se narodili ve stejné datum jako student Michael Silverman s tolerancí 3 měsíce.
SELECT Student.fname, Student.lname
FROM Student ms, Student
WHERE
    ms.fname = 'Michael' AND ms.lname = 'Silverman' AND
    Student.date_of_birth BETWEEN ADD_MONTHS(ms.date_of_birth, -3) AND ADD_MONTHS(ms.date_of_birth, +3)

-- 5.1. Vypište celá jména všech učitelů převedená na velká písmena. Celé jméno bude tvořeno jménem, mezerou a příjmením.
SELECT UPPER(fname || ' ' || lname) AS full_name
FROM Teacher

-- 5.2. Pro každého učitele vypište délku (počet znaků) jeho příjmení.
SELECT fname, lname, LENGTH(lname) AS len
FROM Teacher

-- 5.3. Vypište názvy všech kurzů bez mezer, tj. např. 'Discrete Math' bude vypsáno jako 'DiscreteMath'.
SELECT REPLACE(name, ' ', '') AS name_without_spaces
FROM Course

-- 5.4. Pro všechny kurzy vypište jejich kapacitu zarovnanou na 3 číslice, tj. např. kapacita 5 bude vypsána jako '005'.
SELECT code, LPAD(capacity, 3, '0') AS padded_cap
FROM Course

-- 5.5. Vypište podřetězce kódů kurzů mezi 5-tým až 7-mým znakem, tj. mezi pomlčkami.
SELECT code, SUBSTR(code, 5, 3)
FROM Course

-- 5.6. Vypište názvy kurzů s vynecháním prvních dvou znaků.
SELECT name, SUBSTR(name, 3, LENGTH(name) - 2)
FROM Course

-- 5.7. Pro všechny kurzy vypište pozici první mezery v jejich názvu.
SELECT name, INSTR(name, ' ') AS first_space
FROM Course



------------------------------------------------------------------------------------------------------------ 2


-- 1.1

SET SERVEROUTPUT ON;

-- 1.2

BEGIN
    dbms_output.put_line('Hello World!');
END;

------------------------------------------------------------------------------------------------------

-- 2.1

BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('abc123', 'Petr', 'Novak', 'petr.novak@vsb.cz', 1, TO_DATE('1992/05/06', 'yyyy/mm/dd'));
END;

-- 2.2

BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('abc123', 'Petr', 'Novak', 'petr.novak@vsb.cz', 1, TO_DATE('1992/05/06', 'yyyy/mm/dd'));

    dbms_output.put_line('Student byl vlozen.');
EXCEPTION
    WHEN OTHERS THEN
        dbms_output.put_line('Student nebyl vlozen.');
END;

-- 2.3

DECLARE
    v_login CHAR(6);
    v_fname VARCHAR2(30);
    v_lname VARCHAR2(30);
    v_email VARCHAR2(50);
    v_grade INTEGER;
    v_date DATE;
BEGIN
    v_login := 'abc123';
    v_fname := 'Petr';
    v_lname := 'Novak';
    v_email := 'petr.novak@vsb.cz';
    v_grade := 1;
    v_date := TO_DATE('1992/05/06', 'yyyy/mm/dd');
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, v_fname, v_lname, v_email, v_grade, v_date);

    dbms_output.put_line('Student byl vlozen.');
EXCEPTION
    WHEN OTHERS THEN
        dbms_output.put_line('Student nebyl vlozen.');    
END;

-- 2.4

DECLARE
    v_login Student.login%TYPE;
    v_fname Student.fname%TYPE;
    v_lname Student.lname%TYPE;
    v_email Student.email%TYPE;
    v_grade Student.grade%TYPE;
    v_date Student.date_of_birth%TYPE;
BEGIN
    v_login := 'abc123';
    v_fname := 'Petr';
    v_lname := 'Novak';
    v_email := 'petr.novak@vsb.cz';
    v_grade := 1;
    v_date := TO_DATE('1992/05/06', 'yyyy/mm/dd');
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, v_fname, v_lname, v_email, v_grade, v_date);

    dbms_output.put_line('Student byl vlozen.');
EXCEPTION
    WHEN OTHERS THEN
        dbms_output.put_line('Student nebyl vlozen.');    
END;

------------------------------------------------------------------------------------------------------

-- 3.1

DECLARE
    v_login Student.login%TYPE;
    v_fname Student.fname%TYPE;
    v_lname Student.lname%TYPE;
    v_email Student.email%TYPE;
    v_grade Student.grade%TYPE;
    v_date Student.date_of_birth%TYPE;
    
BEGIN
    SELECT login, fname, lname, email, grade, date_of_birth INTO v_login, v_fname, v_lname, v_email, v_grade, v_date
    FROM Student
    WHERE login = 'abc123';
    
    dbms_output.put_line('login:         ' || v_login);
    dbms_output.put_line('fname:         ' || v_fname);
    dbms_output.put_line('lname:         ' || v_lname);
    dbms_output.put_line('email:         ' || v_email);
    dbms_output.put_line('grade:         ' || v_grade);
    dbms_output.put_line('date_of_birth: ' || v_date);
END;

-- 3.2

DECLARE
    v_student Student%ROWTYPE;
    
BEGIN
    SELECT * INTO v_student
    FROM Student
    WHERE login = 'abc123';
    
    dbms_output.put_line('login:         ' || v_student.login);
    dbms_output.put_line('fname:         ' || v_student.fname);
    dbms_output.put_line('lname:         ' || v_student.lname);
    dbms_output.put_line('email:         ' || v_student.email);
    dbms_output.put_line('grade:         ' || v_student.grade);
    dbms_output.put_line('date_of_birth: ' || v_student.date_of_birth);
END;

-- 3.3

DECLARE
    v_student Student%ROWTYPE;
    
BEGIN
    SELECT * INTO v_student
    FROM Student
    WHERE login = 'abc123';
    
    dbms_output.put_line('login:         ' || v_student.login);
    dbms_output.put_line('fname:         ' || v_student.fname);
    dbms_output.put_line('lname:         ' || v_student.lname);
    dbms_output.put_line('email:         ' || v_student.email);
    dbms_output.put_line('grade:         ' || v_student.grade);
    dbms_output.put_line('date_of_birth: ' || v_student.date_of_birth);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        dbms_output.put_line('Nenalezen zadny zaznam.');
    WHEN TOO_MANY_ROWS THEN
        dbms_output.put_line('Prilis mnoho radku.');
END;

-- 3.4

-- Priklad pro vyjimku NO_DATA_FOUND.
DECLARE
    v_student Student%ROWTYPE;
    
BEGIN
    SELECT * INTO v_student
    FROM Student
    WHERE login = 'xxx000'; -- Takovyto login nema zadny student v databazi.   
    
    dbms_output.put_line('login:         ' || v_student.login);
    dbms_output.put_line('fname:         ' || v_student.fname);
    dbms_output.put_line('lname:         ' || v_student.lname);
    dbms_output.put_line('email:         ' || v_student.email);
    dbms_output.put_line('grade:         ' || v_student.grade);
    dbms_output.put_line('date_of_birth: ' || v_student.date_of_birth);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        dbms_output.put_line('Nenalezen zadny zaznam.');
    WHEN TOO_MANY_ROWS THEN
        dbms_output.put_line('Prilis mnoho radku.');
END;

-- Priklad pro vyjimku TOO_MANY_ROWS.
DECLARE
    v_student Student%ROWTYPE;
    
BEGIN
    SELECT * INTO v_student
    FROM Student
    WHERE grade = 1; -- Existuje vice studentu s rocnikem 1.   
    
    dbms_output.put_line('login:         ' || v_student.login);
    dbms_output.put_line('fname:         ' || v_student.fname);
    dbms_output.put_line('lname:         ' || v_student.lname);
    dbms_output.put_line('email:         ' || v_student.email);
    dbms_output.put_line('grade:         ' || v_student.grade);
    dbms_output.put_line('date_of_birth: ' || v_student.date_of_birth);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        dbms_output.put_line('Nenalezen zadny zaznam.');
    WHEN TOO_MANY_ROWS THEN
        dbms_output.put_line('Prilis mnoho radku.');
END;

------------------------------------------------------------------------------------------------------
-- 4.1

BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('svo001', 'Josef', 'Svoboda', 'josef.svoboda@vsb.cz', 1, TO_DATE('1993/07/02', 'yyyy/mm/dd'));

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('cer001', 'Jana', 'Cerna', 'jana.cerna@vsb.cz', 2, TO_DATE('1991/12/05', 'yyyy/mm/dd'));

    COMMIT;

    dbms_output.put_line('OK');
    
EXCEPTION  
    WHEN OTHERS THEN
        ROLLBACK;
        dbms_output.put_line('Chyba');
END;

-- 4.2

BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('svo002', 'Josef', 'Svoboda', 'josef.svoboda@vsb.cz', 1, TO_DATE('1993/07/02', 'yyyy/mm/dd'));

    -- Napr. zopakovanim stejneho INSERT by doslo k vlozeni duplicitni hodnoty PK, coz vyvola vyjimku.
    -- Po rollback tedy nebude vlozen ani jeden student svo002.
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('svo002', 'Josef', 'Svoboda', 'josef.svoboda@vsb.cz', 1, TO_DATE('1993/07/02', 'yyyy/mm/dd'));

    COMMIT;
    dbms_output.put_line('OK');
    
EXCEPTION  
    WHEN OTHERS THEN
        ROLLBACK;
        dbms_output.put_line('Chyba');
END;

------------------------------------------------------------------------------------------------------

-- DU 1

DECLARE
    v_student Student%ROWTYPE;
    v_studentCourse StudentCourse%ROWTYPE;
    v_course Course%ROWTYPE;
    v_teacher Teacher%ROWTYPE;

BEGIN
    v_student.login := 'chy001';
    v_student.fname := 'Jiri';
    v_student.lname := 'Chytry';
    v_student.email := 'jiri.chytry@vsb.cz';
    v_student.grade := 1;
    v_student.date_of_birth := TO_DATE('1990/03/03', 'yyyy/mm/dd');

    v_teacher.login := 'pri001';    
    v_teacher.fname := 'Karel';
    v_teacher.lname := 'Prisny';
    v_teacher.department := 'Department of Computer Science';
    
    v_course.code := '460-ds2-022';
    v_course.name := 'Databazove Systemy II';
    v_course.capacity := 10;
    v_course.teacher_login := 'pri001';
    
    v_studentCourse.student_login := 'chy001';
    v_studentCourse.course_code := '460-ds2-022';
    v_studentCourse.year := 2022;
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_student.login, v_student.fname, v_student.lname, v_student.email, v_student.grade, v_student.date_of_birth);
    
    INSERT INTO Teacher (login, fname, lname, department)
    VALUES (v_teacher.login, v_teacher.fname, v_teacher.lname, v_teacher.department);
    
    INSERT INTO Course (code, name, capacity, teacher_login)
    VALUES (v_course.code, v_course.name, v_course.capacity, v_course.teacher_login);
    
    INSERT INTO StudentCourse (student_login, course_code, year)
    VALUES (v_studentCourse.student_login, v_studentCourse.course_code, v_studentCourse.year);
    
    COMMIT;
    dbms_output.put_line('Skript uspesne dokoncen.');

EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;    
        dbms_output.put_line('Pri zpracovani skriptu doslo k chybe.');
END;

-- DU 2
DECLARE
    v_login1 Teacher.login%TYPE := 'jor012';
    v_login2 Teacher.login%TYPE := 'per085';

BEGIN
    INSERT INTO Teacher (login, fname, lname, department)
    VALUES ('tmp999', 'Temporary', 'Teacher', 'Temp');

    UPDATE Course
    SET teacher_login = 'tmp999'
    WHERE teacher_login = v_login1;

    UPDATE Course
    SET teacher_login = v_login1
    WHERE teacher_login = v_login2;

    UPDATE Course
    SET teacher_login = v_login2
    WHERE teacher_login = 'tmp999';

    DELETE FROM Teacher
    WHERE login = 'tmp999';

    COMMIT;
    
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
END;


------------------------------------------------------------------------------------------------------------ 3


-- 1.1
CREATE OR REPLACE PROCEDURE PPrint(p_text VARCHAR2) AS
BEGIN
    dbms_output.put_line(p_text);
END;

-- 1.2
CREATE OR REPLACE PROCEDURE PAddStudent1(p_login Student.login%TYPE, p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) AS
BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (p_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;

-- 1.3
CREATE OR REPLACE PROCEDURE PAddStudent2(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) AS
    
    v_login Student.login%TYPE;
BEGIN
    v_login := LOWER(SUBSTR(p_lname, 1, 3)) || '000';
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;

-- 1.4
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

--------------------------------------------------------------------------------------------------------------------------------

-- 2.1
CREATE OR REPLACE FUNCTION FAddStudent1(p_login Student.login%TYPE, p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS
BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (p_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
    
    RETURN 'OK';
EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;

-- Ukazka volani funkce.
EXECUTE PPrint(FAddStudent1('abc123', 'Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd')));

-- 2.2
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

-- Ukazka volani funkce.
EXECUTE PPrint(FAddStudent2('Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd')));

-- 2.3
CREATE OR REPLACE FUNCTION FGetLogin(p_lname Student.lname%TYPE) RETURN Student.login%TYPE AS
    v_studentCount INT;
BEGIN   
    SELECT COUNT(*) + 1 INTO v_studentCount
    FROM Student;

    RETURN LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_studentCount, 3, '0');
END;

-- 2.4
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

--------------------------------------------------------------------------------------------------------------------------------

-- 3.1
CREATE OR REPLACE TRIGGER TInsertStudent AFTER INSERT ON Student FOR EACH ROW
BEGIN
    PPrint(:new.login || ': ' || :new.fname || ' ' || :new.lname);
END;

-- Ukazka volani. Po zavolani se do konzoloveho vystupu musi vypsat login a jmeno studenta.
EXECUTE PAddStudent3('Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd'));

-- 3.2
CREATE OR REPLACE TRIGGER TDeleteStudent BEFORE DELETE ON Student FOR EACH ROW
BEGIN
    PPrint(:old.login || ': ' || :old.fname || ' ' || :old.lname);
END;

DELETE FROM Student
WHERE login = 'nov000'; -- (doplnit login naposledy vlozeneho studenta)

-- 3.3
CREATE OR REPLACE TRIGGER TUpdateStudent AFTER UPDATE ON Student FOR EACH ROW
BEGIN
    PPrint('Pred zmenou: ' || :old.fname || ' ' || :old.lname || ', rocnik ' || :old.grade);
    PPrint('Po zmene:    ' || :new.fname || ' ' || :new.lname || ', rocnik ' || :new.grade);
END;

UPDATE Student
SET grade = grade + 1
WHERE login IN ('mcc676', 'kow007');

-- 3.4
CREATE OR REPLACE TRIGGER TInsertStudent1 AFTER INSERT ON Student FOR EACH ROW
DECLARE
    v_login Student.login%TYPE;
    v_year INT;
BEGIN
    v_login := :new.login;
    v_year := EXTRACT(YEAR FROM CURRENT_TIMESTAMP);

    INSERT INTO StudentCourse (student_login, course_code, year)
    SELECT v_login, code, v_year
    FROM Course
    WHERE grade = 1;
END;

-- 3.5
CREATE OR REPLACE TRIGGER TInsertStudent2 BEFORE INSERT ON Student FOR EACH ROW
BEGIN
    :new.login := FGetLogin(:new.lname);
END;

INSERT INTO Student (fname, lname, email, grade, date_of_birth)
VALUES ('Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd'));

-- 3.6
DROP TRIGGER TInsertStudent;
DROP TRIGGER TDeleteStudent;
DROP TRIGGER TUpdateStudent;
DROP TRIGGER TInsertStudent1;
DROP TRIGGER TInsertStudent2;

--------------------------------------------------------------------------------------------------------------------------------

-- 4.1
CREATE OR REPLACE PROCEDURE PStudentBecomeTeacher(p_login Student.login%TYPE,
    p_department Teacher.department%TYPE) AS

BEGIN
    INSERT INTO Teacher (login, fname, lname, department)
    SELECT login, fname, lname, p_department
    FROM Student
    WHERE login = p_login;
    
    DELETE FROM Student
    WHERE login = p_login;

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
END;

-- 4.2
CREATE OR REPLACE PROCEDURE PStudentAssignment(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_dateOfBirth DATE) AS
    
    v_login Student.login%TYPE;
    v_email Student.email%TYPE;
    v_year StudentCourse.year%TYPE;
BEGIN
    v_login := FGetLogin(p_lname);
    v_email := v_login || '@vsb.cz';
    v_year := EXTRACT(YEAR FROM CURRENT_TIMESTAMP);
    
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, v_email, 1, p_dateOfBirth);
    
    INSERT INTO StudentCourse (student_login, course_code, year)
    SELECT v_login, code, v_year
    FROM Course
    WHERE grade = 1;

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;    
END;

--------------------------------------------------------------------------------------------------------------------------------

-- Domaci ulohy

-- DU 1/1

CREATE OR REPLACE PROCEDURE PSendEMail(p_email VARCHAR2, p_subject VARCHAR2, p_body VARCHAR2) AS
BEGIN
    PPrint('-----------------------------------------------------------------------------');
    PPrint('e-mail to: ' || p_email || ', subject: ' || p_subject);
    PPrint(p_body);
    PPrint('-----------------------------------------------------------------------------');
END;

-- DU 1/2

CREATE OR REPLACE TRIGGER TSendEMail AFTER INSERT ON StudentCourse FOR EACH ROW
DECLARE
    v_student_fname Student.fname%TYPE;
    v_student_lname Student.lname%TYPE;
    v_student_email Student.email%TYPE;
    v_teacher_fname Teacher.fname%TYPE;
    v_teacher_lname Teacher.lname%TYPE;
    v_course_name Course.name%TYPE;
    v_subject VARCHAR2(100);
    v_body VARCHAR2(500);
BEGIN
    SELECT fname, lname, email INTO v_student_fname, v_student_lname, v_student_email
    FROM Student
    WHERE login = :new.student_login;
    
    SELECT Course.name, Teacher.fname, Teacher.lname INTO v_course_name, v_teacher_fname, v_teacher_lname
    FROM Teacher JOIN Course ON Teacher.login = Course.teacher_login
    WHERE Course.code = :new.course_code;
    
    v_subject := 'Prihlaseni ke kurzu ' || v_course_name;
    
    v_body := 'Vazeny studente ' || v_student_fname || ' ' || v_student_lname || ', dne ' || TO_CHAR(CURRENT_TIMESTAMP, 'dd.mm.yyyy hh24:mi:ss') ||
        ' jste byl prihlasen do kurzu ' || v_course_name || '. Vyucujicim kurzu je ' || v_teacher_fname ||
        ' ' || v_teacher_lname || '.';
        
    PSendEMail(v_student_email, v_subject, v_body);
END;

--------------------------------------------------------------------------------------------------------------------------------

-- DU 2/1

CREATE OR REPLACE FUNCTION FGetStudentScore(p_login Student.login%TYPE) RETURN NUMBER AS
    v_ptsReceived INT;
    v_ptsTotal INT;
BEGIN
    SELECT COALESCE(SUM(points), 0), COUNT(*) * 100 INTO v_ptsReceived, v_ptsTotal
    FROM StudentCourse
    WHERE student_login = p_login;
    
    RETURN v_ptsReceived / v_ptsTotal;
END;

-- DU 2/2

CREATE OR REPLACE PROCEDURE PCheckStudents(p_amount NUMBER) AS
    v_avgPts NUMBER;
BEGIN
    SELECT AVG(sum_points) INTO v_avgPts
    FROM
    (
        SELECT SUM(points) AS sum_points
        FROM StudentCourse
        GROUP BY student_login
    ) T;
    
    UPDATE Student
    SET account_balance = account_balance + p_amount
    WHERE
    (
        SELECT SUM(points)
        FROM StudentCourse
        WHERE StudentCourse.student_login = Student.login
    ) > v_avgPts;

    UPDATE Student
    SET account_balance = account_balance - p_amount
    WHERE
    (
        SELECT SUM(points)
        FROM StudentCourse
        WHERE StudentCourse.student_login = Student.login
    ) < v_avgPts;
    
    DELETE FROM Student
    WHERE account_balance < 0;
    
    COMMIT;
    
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
END;


------------------------------------------------------------------------------------------------------------ 4


-- 1.1

CREATE OR REPLACE PROCEDURE PAddStudentToCourse(p_student_login Student.login%TYPE, p_course_code Course.code%TYPE, p_year INT) AS
    v_capacity INT;
    v_cnt INT;
BEGIN
    SELECT capacity INTO v_capacity
    FROM Course
    WHERE code = p_course_code;

    SELECT COUNT(*) INTO v_cnt
    FROM StudentCourse
    WHERE course_code = p_course_code;
    
    if v_cnt < v_capacity THEN
        INSERT INTO StudentCourse (student_login, course_code, year)
        VALUES (p_student_login, p_course_code, p_year);
    ELSE
        PPrint('Kurz je jiz plne obsazen.');
    END IF;
END;


-- 1.2

CREATE OR REPLACE TRIGGER TInsertStudentCourse BEFORE INSERT ON StudentCourse FOR EACH ROW
DECLARE
    v_capacity INT;
    v_cnt INT;
BEGIN
    SELECT capacity INTO v_capacity
    FROM Course
    WHERE code = :new.course_code;

    SELECT COUNT(*) INTO v_cnt
    FROM StudentCourse
    WHERE course_code = :new.course_code;
    
    IF v_cnt >= v_capacity THEN
        PPrint('Kurz je jiz plne obsazen.');
    END IF;
END;

-- 1.3
CREATE OR REPLACE TRIGGER TInsertStudentCourse BEFORE INSERT ON StudentCourse FOR EACH ROW
DECLARE
    v_capacity INT;
    v_cnt INT;
    v_capacity_exceeded EXCEPTION;
BEGIN
    SELECT capacity INTO v_capacity
    FROM Course
    WHERE code = :new.course_code;

    SELECT COUNT(*) INTO v_cnt
    FROM StudentCourse
    WHERE course_code = :new.course_code;
    
    IF v_cnt >= v_capacity THEN
        RAISE v_capacity_exceeded;
    END IF;
END;

--------------------------------------------------------------------------------------------------------------------------------

-- 1.4

CREATE OR REPLACE FUNCTION FAddStudent4(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS
    
    v_login Student.login%TYPE;
    v_gradeCapacity INT;
    v_cnt INT;
BEGIN
    v_login := FGetLogin(p_lname);

    IF p_grade = 1 THEN
        v_gradeCapacity := 20;
    ELSIF p_grade = 2 THEN
        v_gradeCapacity := 15;
    ELSE
        v_gradeCapacity := 10;
    END IF;
    
    SELECT COUNT(*) INTO v_cnt
    FROM Student
    WHERE grade = p_grade;

    IF v_cnt >= v_gradeCapacity THEN
        RETURN 'full';
    END IF;

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    RETURN v_login;

EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;

-- 1.5

CREATE OR REPLACE PROCEDURE PDeleteTeacher(p_login Teacher.login%TYPE) AS
    v_teacherLogin Teacher.login%TYPE;
    v_otherTeachers INT;
    v_noOtherTeacher EXCEPTION;
BEGIN
    SELECT COUNT(*) INTO v_otherTeachers
    FROM Teacher
    WHERE login <> p_login;
    
    IF v_otherTeachers = 0 THEN
        RETURN;
    END IF;

    SELECT Teacher.login INTO v_teacherLogin
    FROM Teacher LEFT JOIN Course ON Teacher.login = Course.teacher_login
    WHERE Teacher.login <> p_login
    GROUP BY Teacher.login
    ORDER BY COUNT(Course.code)
    FETCH FIRST 1 ROWS ONLY;
    
    UPDATE Course
    SET teacher_login = v_teacherLogin
    WHERE teacher_login = p_login;
    
    DELETE FROM Teacher
    WHERE login = p_login;

    COMMIT;
    
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
END;

--------------------------------------------------------------------------------------------------------------------------------

-- 2.1

CREATE OR REPLACE FUNCTION FLoginExists(p_login Student.login%TYPE) RETURN BOOLEAN AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM Student
    WHERE login = p_login;
    
    IF v_cnt > 0 THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END;

-- 2.2

CREATE OR REPLACE FUNCTION FGetNextLogin(p_lname VARCHAR) RETURN VARCHAR AS
    v_i INT;
    v_login VARCHAR(6);
BEGIN
    v_i := 1;
    
    LOOP
        v_login := LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_i, 3, '0');
        EXIT WHEN NOT FLoginExists(v_login);
        v_i := v_i + 1;
    END LOOP;

    RETURN v_login;
END;

-- 2.3

CREATE OR REPLACE FUNCTION FAddStudent4(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS
    
    v_login Student.login%TYPE;
    v_gradeCapacity INT;
    v_cnt INT;
BEGIN
    v_login := FGetNextLogin(p_lname);

    IF p_grade = 1 THEN
        v_gradeCapacity := 20;
    ELSIF p_grade = 2 THEN
        v_gradeCapacity := 15;
    ELSE
        v_gradeCapacity := 10;
    END IF;
    
    SELECT COUNT(*) INTO v_cnt
    FROM Student
    WHERE grade = p_grade;

    IF v_cnt >= v_gradeCapacity THEN
        RETURN 'full';
    END IF;

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    RETURN v_login;

EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;

--------------------------------------------------------------------------------------------------------------------------------

-- 3.1

-- explicitni kurzor
DECLARE
    v_fname Student.fname%TYPE;
    v_lname Student.lname%TYPE;
    CURSOR c_student IS SELECT fname, lname FROM Student;
BEGIN
    OPEN c_student;
    
    LOOP
        EXIT WHEN c_student%NOTFOUND;
        FETCH c_student INTO v_fname, v_lname;
        
        PPrint(v_fname || ' ' || v_lname);
    END LOOP;
    
    CLOSE c_student;
END;

-- kurzor FOR LOOP;
BEGIN
    FOR c_student IN (SELECT fname, lname FROM Student) LOOP
        PPrint(c_student.fname || ' ' || c_student.lname);
    END LOOP;
END;

-- 3.2

CREATE OR REPLACE PROCEDURE PAwardStudents(p_year INT, p_amount NUMBER) AS
    v_i INT := 0;
    v_amount NUMBER := p_amount;
BEGIN
    FOR c_student IN (
        SELECT student_login, SUM(points) AS pts
        FROM StudentCourse
        WHERE year = p_year
        GROUP BY student_login
        ORDER BY pts DESC
    ) LOOP
        EXIT WHEN v_i >= 5;
    
        UPDATE Student
        SET account_balance = account_balance + v_amount
        WHERE login = c_student.student_login;
        
        v_amount := v_amount / 2;
        v_i := v_i + 1;
    END LOOP;
END;

-- 3.3

CREATE OR REPLACE FUNCTION FExportPointsCSV(p_year INT) RETURN VARCHAR AS
    v_ret VARCHAR(1024);
BEGIN
    v_ret := '';

    FOR c_student IN (
        SELECT Student.login, Student.fname, Student.lname, SUM(StudentCourse.points) AS pts
        FROM Student JOIN StudentCourse ON Student.login = StudentCourse.student_login
        WHERE year = p_year
        GROUP BY Student.login, Student.fname, Student.lname
        ORDER BY pts DESC
    ) LOOP
        v_ret := v_ret || c_student.login || ',' || c_student.fname || ',' || c_student.lname || ',' || c_student.pts || CHR(13) || CHR(10);            
    END LOOP;

    RETURN v_ret;
END;

-- DU1

CREATE OR REPLACE FUNCTION FAllSubjectsPass(p_login Student.login%TYPE) RETURN BOOLEAN AS
    v_grade Student.grade%TYPE;
    v_cnt INT;
BEGIN
    SELECT grade INTO v_grade
    FROM Student
    WHERE login = p_login;

    SELECT COUNT(*) INTO v_cnt
    FROM
        Course
        LEFT JOIN StudentCourse ON Course.code = StudentCourse.course_code AND StudentCourse.student_login = p_login
    WHERE grade = v_grade AND COALESCE(StudentCourse.points, 0) < 51;
    
    IF v_cnt > 0 THEN
        RETURN FALSE;
    ELSE
        RETURN TRUE;
    END IF;
END;

CREATE OR REPLACE FUNCTION FNextGrade(p_login Student.login%TYPE) RETURN INT AS
    v_currentGrade Student.grade%TYPE;
BEGIN
    SELECT grade INTO v_currentGrade
    FROM Student
    WHERE login = p_login;
    
    IF v_currentGrade < 5 THEN
        RETURN v_currentGrade + 1;
    ELSE
        RETURN -1;
    END IF;
END;

CREATE OR REPLACE PROCEDURE PSetFreeCourses(p_login Student.login%TYPE) AS 
    v_year StudentCourse.year%TYPE;
    v_grade Student.grade%TYPE;
BEGIN
    v_year := EXTRACT(YEAR FROM CURRENT_TIMESTAMP);
    
    SELECT grade INTO v_grade
    FROM Student
    WHERE login = p_login;
    
    INSERT INTO StudentCourse(student_login, course_code, year)
    SELECT p_login, code, v_year
    FROM Course
    WHERE grade = v_grade AND (
        SELECT COUNT(*)
        FROM StudentCourse
        WHERE year = v_year AND StudentCourse.course_code = Course.code AND COALESCE(StudentCourse.points, 0) < 51
        ) < Course.capacity;
END;

CREATE OR REPLACE PROCEDURE PMoveToNextGrade AS
    v_nextGrade INT;
BEGIN
    FOR c_student IN (SELECT login FROM Student ORDER BY grade DESC) LOOP
        IF FAllSubjectsPass(c_student.login) THEN
            v_nextGrade := FNextGrade(c_student.login);
            
            UPDATE Student
            SET grade = v_nextGrade
            WHERE login = c_student.login;
            
            PSetFreeCourses(c_student.login);
        END IF;
    END LOOP;
END;

-- DU 2

CREATE OR REPLACE FUNCTION FGetCreateScript(p_tableName VARCHAR2) 
return VARCHAR2
as
  cursor c_columns is select * from user_tab_columns where table_name = UPPER(p_tableName) order by column_id;
  v_command VARCHAR2(1000);
begin
  v_command := 'CREATE TABLE ' || UPPER(p_tableName) || '_OLD (';
  for one_column in c_columns loop
    if c_columns%ROWCOUNT > 1 then
      v_command := v_command || ',';
    end if;
      v_command := v_command || ' ' || one_column.column_name || ' ' || one_column.data_type || '(' || one_column.data_length || ')';
  end loop;
  v_command := v_command || ')';  
  
  return v_command;
end;

create or replace TRIGGER TChangeCourseCapacity
BEFORE UPDATE ON COURSE
FOR EACH ROW
DECLARE
  studentsCount integer;
  e_no_change exception;
BEGIN
  if (:NEW.Capacity < :OLD.Capacity) then
    select count(*) into studentsCount from studentcourse where course_code = :NEW.code and (points is null or points < 51);
    if (studentsCount > :NEW.Capacity) then
      RAISE e_no_change;
    end if;
  elsif (:NEW.Capacity > :OLD.Capacity) then
    studentsCount := :NEW.Capacity - :OLD.Capacity;
    for student in (select login from student 
                    where grade = :NEW.grade 
                      and login not in (select login from studentcourse 
                                        where course_code = :NEW.code) 
                    order by lname asc) loop
      insert into studentcourse (student_login, course_code, year, points) values (student.login, :NEW.code, EXTRACT(YEAR FROM CURRENT_TIMESTAMP), 0); 
      studentsCount := studentsCount - 1;
      if (studentsCount = 0) then
        exit;
      end if;  
    end loop;
  end if;
exception
   WHEN e_no_change THEN
     dbms_output.put_line('Error');
     RAISE;
END;



------------------------------------------------------------------------------------------------------------ 5


-- 1.1

CREATE OR REPLACE PROCEDURE PPrepareTableReward AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM user_tables
    WHERE table_name = 'REWARD';
    
    IF v_cnt > 0 THEN
        EXECUTE IMMEDIATE ('DROP TABLE Reward');
    END IF;

    EXECUTE IMMEDIATE ('
CREATE TABLE Reward 
(
    id INTEGER PRIMARY KEY,
    student_login CHAR(6) REFERENCES Student,
    winter_reward INTEGER NULL,
    summer_reward INTEGER NULL,
    thesis_reward INTEGER NULL
)');
END;

-- 1.2

CREATE OR REPLACE PROCEDURE PSetStudentReward(p_login Student.login%TYPE, p_rewardType VARCHAR, p_reward INTEGER) AS
    v_id INT;
    v_sql VARCHAR(500);
BEGIN
    SELECT COALESCE(MAX(ID), 0) + 1 INTO v_id
    FROM Reward;

    v_sql := 'INSERT INTO Reward (id, student_login, ' || p_rewardType || '_reward) VALUES (:1, :2, :3)';
    
    EXECUTE IMMEDIATE v_sql USING v_id, p_login, p_reward;
END;

--------------------------------------------------------------------------------------------------------------------------------

-- 2.1

CREATE OR REPLACE PROCEDURE PUpdateGradeStatic(p_grade Student.grade%TYPE, p_fname Student.fname%TYPE,
    p_lname Student.lname%TYPE) AS
BEGIN
    UPDATE Student
    SET grade = p_grade
    WHERE fname = p_fname AND lname = p_lname;
END;

-- 2.2
CREATE OR REPLACE PROCEDURE PUpdateGradeDynamic(p_grade Student.grade%TYPE, p_fname Student.fname%TYPE,
    p_lname Student.lname%TYPE) AS

    v_whereStatement VARCHAR(100) := '(1=1)';
BEGIN
    IF p_fname IS NOT NULL THEN
        v_whereStatement := v_whereStatement || ' AND fname = ''' || p_fname || '''';
    END IF;

    IF p_lname IS NOT NULL THEN
        v_whereStatement := v_whereStatement || ' AND lname = ''' || p_lname || '''';
    END IF;

    EXECUTE IMMEDIATE ('
UPDATE Student
SET grade = :1
WHERE ' || v_whereStatement) USING p_grade;

END;


-- 2.3
CREATE OR REPLACE PROCEDURE PUpdateGrade(p_grade Student.grade%TYPE, p_fname Student.fName%TYPE,
    p_lname Student.lName%TYPE, p_type VARCHAR) AS
    
    v_sql VARCHAR(100);
BEGIN
    v_sql := 'BEGIN PUpdateGrade' || p_type || '(:1, :2, :3); END;';
    EXECUTE IMMEDIATE v_sql USING p_grade, p_fname, p_lname;
END;

EXEC PUpdateGrade(4, 'Jan', NULL, 'Dynamic');


--------------------------------------------------------------------------------------------------------------------------------

-- DU 1
CREATE OR REPLACE FUNCTION FGetStudentInfo1(p_login Student.login%TYPE) RETURN VARCHAR AS
    v_ret VARCHAR(500);
BEGIN
    SELECT 'login = ' || login || '; fName = ' || fname || '; lname = ' || lname || '; email = ' || email || '; grade = ' ||
        grade || '; date_of_birth = ' || date_of_birth || '; account_balance = ' || account_balance
    INTO v_ret
    FROM Student
    WHERE login = p_login;
    
    RETURN v_ret;
END;

-- DU 2
CREATE OR REPLACE FUNCTION FGetStudentInfo2(p_login Student.login%TYPE, p_attributes VARCHAR) RETURN VARCHAR AS
    v_ret VARCHAR(500);

    v_attribute VARCHAR(100);
    p_index INT := 1;
    p_indexOld INT := 1;
    p_exit BOOLEAN := FALSE;
    
    v_selectSql VARCHAR(1000);
    v_querySql VARCHAR(1000);
BEGIN
    v_selectSql := NULL;
    LOOP
        p_index := INSTR(p_attributes, ';', p_index);

        IF p_index = 0 THEN
            p_exit := TRUE;
            p_index := LENGTH(p_attributes) + 1;
        END IF;
                
        v_attribute := SUBSTR(p_attributes, p_indexOld, p_index - p_indexOld);
        
        IF v_selectSql IS NOT NULL THEN
            v_selectSql := v_selectSql || ' || ''; '' || ';
        END IF;
        
        v_selectSql := v_selectSql || '''' || v_attribute || ' = '' || ' || v_attribute;

        EXIT WHEN p_exit;
        
        p_index := p_index + 1;
        p_indexOld := p_index;
    END LOOP;
    
    v_querySql := 'SELECT ' || v_selectSql || ' FROM Student WHERE login = :1';
    
    EXECUTE IMMEDIATE v_querySql INTO v_ret USING p_login;
    
    RETURN v_ret;
END;







CREATE OR REPLACE FUNCTION InsertConfusedVote( id_hlasovani INT, id_osoba INT, rok NUMBER) RETURN NUMBER AS
    v_cnt_osoba int;
    v_cnt_hlas int;
    v_cnt_zmatecne int;
BEGIN
    SELECT COUNT(*) INTO v_cnt_osoba
    FROM OSOBA o
    WHERE o.ID_OSOBA = id_osoba;

    IF v_cnt_osoba = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Neexistuje');
        return -1;
    end if;

    SELECT COUNT(*) INTO v_cnt_hlas
    FROM HLASOVANI h
    WHERE h.ID_HLASOVANI = id_hlasovani;

    IF v_cnt_hlas = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Neexistuje');
        return -1;
    end if;

    SELECT COUNT(*) INTO v_cnt_zmatecne
    FROM ZMATECNE_HLASOVANI_POSLANEC p
    JOIN HLASOVANI hl ON p.ID_HLASOVANI = hl.ID_HLASOVANI
    WHERE p.ID_OSOBA = id_osoba AND EXTRACT(YEAR FROM hl.datum) = rok;

    IF v_cnt_zmatecne <= 5 THEN
        INSERT INTO zmatecne_hlasovani_poslanec VALUES (id_hlasovani, id_osoba, 0);
    ELSE
        INSERT INTO zmatecne_hlasovani_poslanec VALUES (id_hlasovani, id_osoba, 1);
    END IF;

    DBMS_OUTPUT.PUT_LINE('Zmatené hlasování zaevidováno.');
    COMMIT;
    RETURN v_cnt_zmatecne;
EXCEPTION
   WHEN OTHERS THEN
        ROLLBACK;
        Return -1;
END;











ALTER TABLE SCHUZE
ADD vote_level char(1) CHECK (vote_level IN ('L', 'M', 'H'));

CREATE OR REPLACE PROCEDURE SetVoteLevel( v_od DATE, v_do DATE ) AS
BEGIN
    for rec in(
        SELECT s.SCHUZE, COUNT(hl.schuze) AS p_hl
        FROM SCHUZE s
        LEFT JOIN HLASOVANI hl on s.SCHUZE = hl.SCHUZE
        WHERE hl.DATUM between v_od AND v_do
        GROUP BY s.SCHUZE)
    LOOP
        UPDATE schuze
        SET vote_level =
            CASE
                WHEN rec.p_hl < 100 THEN 'L'
                WHEN rec.p_hl BETWEEN 101 AND 1000 THEN 'M'
                ELSE 'H'
            END
        WHERE SCHUZE = rec.SCHUZE;
    end loop;
    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
END;


select *
from HLASOVANI;





CREATE OR REPLACE TRIGGER before_insert_bod_schuze
BEFORE INSERT ON bod_schuze
FOR EACH ROW
DECLARE
    aktualni_schuze_skoncila EXCEPTION;
    organ_jiz_skoncil EXCEPTION;
    v_od_schuze date;
    v_do_schuze date;
    v_od_organ date;
    v_do_organ date;
BEGIN
   select od_schuze, do_schuze into v_od_schuze, v_do_schuze
   from schuze
   where id_schuze = :NEW.id_schuze;

    -- Kontrola, zda schůze již skončila nebo nezačala
    IF (v_od_schuze > CURRENT_DATE AND v_do_schuze < CURRENT_DATE) THEN
        RAISE aktualni_schuze_skoncila;
    END IF;

   select od_organ, do_organ into v_od_organ, v_do_organ
   from organ join schuze on organ.id_organ = schuze.id_organ
   where id_schuze = :NEW.id_schuze;

    -- Kontrola, zda se bod týká orgánu, který již skončil působení
    IF (v_od_organ > CURRENT_DATE AND v_do_organ < CURRENT_DATE) THEN
        RAISE organ_jiz_skoncil;
    END IF;

    -- Nastavení atributu bod na aktuální počet bodů v dané schůzi + 1
    SELECT COUNT(*) + 1
    INTO :NEW.bod
    FROM bod_schuze
    WHERE id_schuze = :NEW.id_schuze;

    -- Kontrola, zda byl vyplněn úplný název
    IF :NEW.uplny_naz IS NULL OR :NEW.bod = 1 THEN
        :NEW.uplny_naz := 'Úvodní bod';
    END IF;
END;






CREATE OR REPLACE PROCEDURE P_SET_ZARAZENI_ORG( p_id_osoba INT, p_id_organ INT, p_set CHAR) AS
    v_cnt INT;
    org_neexistuje EXCEPTION;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM ORGAN
    WHERE ID_ORGAN = p_id_organ;

    IF v_cnt = 0 THEN
        RAISE org_neexistuje;
        RETURN;
    end if;

    SELECT COUNT(*) INTO v_cnt
    FROM ZARAZENI
    WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
        VALUES (p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
        DELETE FROM zarazeni
        WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;
    END IF;
end;




CREATE OR REPLACE TRIGGER TG_HLASOVANI_POSLANEC AFTER INSERT OR DELETE OR UPDATE ON HLASOVANI_POSLANEC FOR EACH ROW
BEGIN

    IF :NEW.vysledek = 'A' THEN
        UPDATE HLASOVANI
        SET pro = pro + 1
        WHERE hlasovani.ID_HLASOVANI = :new.id_hlasovani;
    end if;

    IF :NEW.vysledek = 'B' THEN
        UPDATE HLASOVANI
        SET proti = proti + 1
        WHERE hlasovani.ID_HLASOVANI = :new.id_hlasovani;
    end if;


    IF :OLD.vysledek = 'A' THEN
        UPDATE HLASOVANI
        SET pro = pro - 1
        WHERE hlasovani.ID_HLASOVANI = :old.id_hlasovani;
    end if;

    IF :OLD.vysledek = 'B' THEN
        UPDATE HLASOVANI
        SET proti = proti - 1
        WHERE hlasovani.ID_HLASOVANI = :OLD.id_hlasovani;
    end if;
end;



DECLARE
    v_pro INT;
    v_proti INT;
BEGIN

    SELECT pro, proti INTO v_pro, v_proti
    FROM hlasovani
    WHERE id_hlasovani = 81577;
    -- pro: 113, proti: 1

    dbms_output.put_line('pro: ' || v_pro || ', proti: ' || v_proti);
END;







create or replace PROCEDURE P_SET_HLASOVANI_POSLANEC(p_id_hlasovani INT, p_id_poslanec INT, p_vysledek CHAR) AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM hlasovani_poslanec
    WHERE id_poslanec = p_id_poslanec AND id_hlasovani = p_id_hlasovani;

    IF v_cnt = 0 THEN
        INSERT INTO hlasovani_poslanec(id_poslanec, id_hlasovani, vysledek)
        VALUES (p_id_poslanec, p_id_hlasovani, p_vysledek);
    ELSE
        UPDATE hlasovani_poslanec
        SET vysledek = p_vysledek
        WHERE id_poslanec = p_id_poslanec AND id_hlasovani = p_id_hlasovani;
    END IF;

    UPDATE hlasovani
    SET pro = (
        SELECT COUNT(*)
        FROM hlasovani_poslanec
        WHERE id_hlasovani = p_id_hlasovani AND vysledek = 'A'
    )
    WHERE id_hlasovani = p_id_hlasovani;

    UPDATE hlasovani
    SET proti = (
        SELECT COUNT(*)
        FROM hlasovani_poslanec
        WHERE id_hlasovani = p_id_hlasovani AND vysledek = 'B'
    )
    WHERE id_hlasovani = p_id_hlasovani;
END;

/

DECLARE
    v_pro INT;
    v_proti INT;
BEGIN
    SELECT pro, proti INTO v_pro, v_proti
    FROM HLASOVANI
    WHERE ID_HLASOVANI = 81577;

    DBMS_OUTPUT.PUT_LINE('pro' || v_pro || 'proti' || v_proti);
END;








CREATE OR REPLACE FUNCTION F_SET (p_id_osoba INT, p_id_organ INT, p_set CHAR) RETURN VARCHAR2 AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM ORGAN
    WHERE ID_ORGAN = p_id_organ;

    IF v_cnt = 0 THEN
        RETURN 'E';
    end if;

    SELECT COUNT(*) INTO v_cnt
    FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

    IF p_set = 'Y' AND v_cnt = 0 THEN
    INSERT INTO zarazeni (id_osoba, id_of, cl_funkce, od_o)
    VALUES (p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);

    RETURN 'I';
    ELSIF p_set = 'N' AND v_cnt > 0 THEN
    DELETE FROM zarazeni
    WHERE id_osoba = p_id_osoba AND id_of = p_id_organ AND cl_funkce = 0;

    RETURN 'D';
    ELSE
    RETURN 'N';
    END IF;
END;



CREATE OR REPLACE TRIGGER tg_zarazeni BEFORE INSERT ON ZARAZENI FOR EACH ROW
DECLARE
    v_cnt INT;
    v_ex EXCEPTION;
BEGIN
    IF :new.cl_funkce = 0 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM ORGAN
        WHERE id_organ = :new.id_of;

        IF v_cnt = 0 THEN
            dbms_output.put_line('Invalid id_organ.');
            RAISE v_ex;
        END IF;
    ELSIF :new.cl_funkce = 1 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM funkce
        WHERE id_funkce = :new.id_of;

        IF v_cnt = 0 THEN
            dbms_output.put_line('Invalid id_funkce.');
            RAISE v_ex;
        END IF;
    ELSE
        dbms_output.put_line('Invalid cl_funkce.');
        RAISE v_ex;
    END IF;
END;



select *
from zarazeni;





















---------------------------------------------------------------------------------------------------------------- ct 9:00
-- A1
CREATE OR REPLACE TRIGGER TG_ZARAZENI BEFORE INSERT OR UPDATE ON ZARAZENI FOR EACH ROW
DECLARE
    v_cnt INT;
    v_ex EXCEPTION;
BEGIN
    IF :new.cl_funkce = 0 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM ORGAN
        WHERE ID_ORGAN = :new.id_of;

        IF v_cnt = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Invalid Organ');
            RAISE v_ex;
        end if;

    elsif :new.cl_funkce = 1 THEN
        SELECT COUNT(*) INTO v_cnt
        FROM FUNKCE
        WHERE ID_FUNKCE = :new.id_of;

        IF v_cnt = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Invalid Funkce');
            RAISE v_ex;
        end if;
    else
        DBMS_OUTPUT.PUT_LINE('Invalid cl_funkce');
    end if;
end;

INSERT INTO ZARAZENI(id_osoba, id_of, cl_funkce, od_o)
VALUES (6755, 1229, 1, CURRENT_TIMESTAMP);


-- A2
CREATE OR REPLACE PROCEDURE p_print_hlasovani(p_id_hlasovani INT) as
    v_prev_vysl CHAR(1) := ' ';
BEGIN
    FOR v_zaz IN (
        select hp.VYSLEDEK, o.JMENO, o.PRIJMENI
        from HLASOVANI_POSLANEC hp
        join POSLANEC p on hp.ID_POSLANEC = p.ID_POSLANEC
        join OSOBA o on p.ID_OSOBA = o.ID_OSOBA
        where hp.ID_HLASOVANI = p_id_hlasovani
        order by hp.VYSLEDEK
    ) LOOP
        if v_prev_vysl != v_zaz.VYSLEDEK THEN
            DBMS_OUTPUT.PUT_LINE('Vysledek ' || v_zaz.VYSLEDEK || ':');
            v_prev_vysl := v_zaz.VYSLEDEK;
        end if;

        DBMS_OUTPUT.PUT_LINE('   * ' || v_zaz.JMENO || ' ' || v_zaz.PRIJMENI);
    end loop;
END;

BEGIN
    P_PRINT_HLASOVANI(29714);
END;




-- B1
CREATE OR REPLACE PROCEDURE P_SET_ZARAZENI_FCE(p_id_osoba INT, p_id_funkce INT, p_set CHAR) AS
    v_cnt INT;
    v_exp EXCEPTION;
begin
    SELECT COUNT(*) INTO v_cnt
    FROM FUNKCE
    WHERE p_id_funkce = ID_FUNKCE;

    if v_cnt = 0 then
        dbms_output.put_line('Function doesnt exist.');
        RAISE v_exp;
    end if;

    SELECT COUNT(*) INTO v_cnt
    FROM ZARAZENI
    WHERE p_id_osoba = ID_OSOBA AND ID_OF = p_id_funkce AND CL_FUNKCE = 1;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO ZARAZENI(id_osoba, id_of, cl_funkce, OD_O)
        VALUES(p_id_osoba, p_id_funkce, 1, CURRENT_TIMESTAMP);

        dbms_output.put_line('Function inserted values');

    ELSIF p_set = 'N' AND v_cnt != 0 THEN
        DELETE FROM ZARAZENI
        WHERE p_id_osoba = ID_OSOBA AND ID_OF = p_id_funkce AND CL_FUNKCE = 1;

        dbms_output.put_line('Function deleted values');
    ELSE
        dbms_output.put_line('Nothing happend');
    end if;
end;

BEGIN
    P_SET_ZARAZENI_FCE(6755, 2930, 'Y');
    P_SET_ZARAZENI_FCE(6755, 2930, 'Y');
    P_SET_ZARAZENI_FCE(6755, 2930, 'N');
    P_SET_ZARAZENI_FCE(6755, 2930, 'N');
END;








--------------------------------------------------------------------------------------------------------------- ct 10:45

CREATE OR REPLACE PROCEDURE P_SET_ZARAZENI_ORG(p_id_osoba INT, p_id_organ INT, p_set CHAR) AS
    v_cnt INT;
    v_exc EXCEPTION;
BEGIN
    SELECT COUNT(*) into v_cnt
    FROM ORGAN
    WHERE p_id_organ = ID_ORGAN;

    IF v_cnt = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Organ does not exist');
        RAISE v_exc;
    end if;

    SELECT COUNT(*) INTO v_cnt
    FROM ZARAZENI
    where p_id_osoba = ID_OSOBA AND p_id_organ = ID_OF AND CL_FUNKCE = 0;

    IF p_set = 'Y' AND v_cnt = 0 THEN
        INSERT INTO ZARAZENI(id_osoba, id_of, CL_FUNKCE, OD_O)
        VALUES(p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);
        DBMS_OUTPUT.PUT_LINE('Person inserted');
    ELSIF p_set = 'N' AND v_cnt != 0 THEN
        DELETE FROM ZARAZENI
        WHERE p_id_osoba = ID_OSOBA AND p_id_organ = ID_OF AND CL_FUNKCE = 0;
        DBMS_OUTPUT.PUT_LINE('Person deleted from database');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Nothing happened');
    end if;
end;


BEGIN
    P_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    P_SET_ZARAZENI_ORG(6755, 1229, 'Y');
    P_SET_ZARAZENI_ORG(6755, 1229, 'N');
    P_SET_ZARAZENI_ORG(6755, 1229, 'N');
END;










CREATE OR REPLACE TRIGGER tg_hlasovani_poslanec AFTER INSERT OR UPDATE OR DELETE ON HLASOVANI_POSLANEC FOR EACH ROW
BEGIN
    IF :old.vysledek = 'A' THEN
        UPDATE HLASOVANI
        SET pro = pro - 1
        WHERE hlasovani.ID_HLASOVANI = :old.id_hlasovani;
    end if;

    IF :new.vysledek = 'A' THEN
        UPDATE HLASOVANI
        SET pro = pro + 1
        WHERE hlasovani.ID_HLASOVANI = :new.id_hlasovani;
    end if;

    IF :old.vysledek = 'B' THEN
        UPDATE HLASOVANI
        SET proti = proti - 1
        WHERE hlasovani.ID_HLASOVANI = :old.id_hlasovani;
    end if;

    IF :new.vysledek = 'B' THEN
        UPDATE HLASOVANI
        SET proti = proti + 1
        WHERE hlasovani.ID_HLASOVANI = :new.id_hlasovani;
    end if;
end;









create or replace procedure p_set_hlasovani_poslanec(p_id_hlasovani INT, p_id_poslanec INT, p_vysledek CHAR) AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM HLASOVANI_POSLANEC
    WHERE ID_POSLANEC = p_id_poslanec AND ID_HLASOVANI = p_id_hlasovani;

    IF v_cnt = 0 THEN
        INSERT INTO HLASOVANI_POSLANEC(id_poslanec, id_hlasovani, vysledek)
        VALUES(p_id_poslanec, p_id_hlasovani, p_vysledek);
    ELSE
        UPDATE HLASOVANI_POSLANEC
        SET VYSLEDEK = p_vysledek
        WHERE ID_HLASOVANI = p_id_hlasovani AND ID_POSLANEC = p_id_poslanec;
    end if;

    update hlasovani
    set pro = (
        SELECT COUNT(*)
        FROM HLASOVANI_POSLANEC
        where VYSLEDEK = 'A' AND p_id_hlasovani = ID_HLASOVANI
    )
    WHERE p_id_hlasovani = ID_HLASOVANI;

    update hlasovani
    set proti = (
        SELECT COUNT(*)
        FROM HLASOVANI_POSLANEC
        where VYSLEDEK = 'B' AND p_id_hlasovani = ID_HLASOVANI
    )
    WHERE p_id_hlasovani = ID_HLASOVANI;
end;


declare
    v_pro INT;
    v_proti INT;
BEGIN
    SELECT pro, proti INTO v_pro, v_proti
    FROM HLASOVANI
    where ID_HLASOVANI = 81577;
    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));




    P_SET_HLASOVANI_POSLANEC(81577, 1942, 'B');
    SELECT pro, proti INTO v_pro, v_proti
    FROM HLASOVANI
    where ID_HLASOVANI = 81577;
    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));


    P_SET_HLASOVANI_POSLANEC(81577, 1942, 'A');
    SELECT pro, proti INTO v_pro, v_proti
    FROM HLASOVANI
    where ID_HLASOVANI = 81577;
    dbms_output.put_line('pro: ' || TO_CHAR(v_pro) || ', proti: ' || TO_CHAR(v_proti));
end;




create or replace function f_set_zarazeni_org(p_id_osoba INT, p_id_organ INT, p_set CHAR) RETURN CHAR AS
    v_cnt INT;
BEGIN
    SELECT COUNT(*) INTO v_cnt
    FROM ORGAN
    WHERE p_id_organ = ID_ORGAN;

    if v_cnt = 0 THEN
        dbms_output.put_line('Organ neexistuje!');
        return 'E';
    end if;

    SELECT COUNT(*) into v_cnt
    FROM ZARAZENI
    WHERE p_id_organ = ID_OF AND p_id_osoba = ID_OSOBA AND CL_FUNKCE = 0;

    if v_cnt = 0 AND p_set = 'Y' THEN
        INSERT INTO ZARAZENI(ID_OSOBA, ID_OF, CL_FUNKCE, OD_O)
        VALUES(p_id_osoba, p_id_organ, 0, CURRENT_TIMESTAMP);
        RETURN 'I';
    elsif v_cnt != 0 AND p_set = 'N' THEN
        DELETE FROM ZARAZENI
        WHERE p_id_organ = ID_OF AND p_id_osoba = ID_OSOBA AND CL_FUNKCE = 0;
        RETURN 'D';
    else
        return 'N';
    end if;
end;


DECLARE
    v_ret CHAR(1);
BEGIN
    v_ret := F_SET_ZARAZENI_ORG(2755, 1229, 'Y');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(2755, 1229, 'Y');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(2755, 1229, 'N');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(2755, 1229, 'N');
    dbms_output.put_line(v_ret);
    v_ret := F_SET_ZARAZENI_ORG(2755, 12290, 'Y');
    dbms_output.put_line(v_ret);
END;





create or replace procedure P_ROZDEL_FUNKCE(p_funkce_od DATE, p_funkce_do DATE) AS
    v_exist INT;
    exc_date EXCEPTION;
BEGIN
    if p_funkce_od >= p_funkce_do OR ( p_funkce_do > CURRENT_DATE ) THEN
        RAISE exc_date;
    end if;

    SElECT COUNT(*) INTO v_exist
    FROM USER_TABLES
    WHERE TABLE_NAME = 'ZARAZENI_FUNKCE';

    if v_exist != 0 THEN
        EXECUTE IMMEDIATE 'DROP TABLE ZARAZENI_FUNKCE';
    end if;

    execute immediate 'CREATE TABLE ZARAZENI_FUNKCE(
                        id_osoba INT REFERENCES OSOBA, id_funkce INT REFERENCES OSOBA, funkce_od DATE, funkce_do DATE)';



end;



