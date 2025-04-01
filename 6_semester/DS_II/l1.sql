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