SET SERVEROUTPUT ON

SELECT DISTINCT

EXEC PAddStudent1(
    'novak000',
    'Jan',
    'Novák',
    'jan.novak@example.com',
    'A',
    DATE '2000-01-15'
);

v_ret := v_ret || c_student.login || ',' || c_student.fname || ',' || c_student.lname || ',' || c_student.pts || CHR(13) || CHR(10);   

-- Tuto strukturu pouzivat kdyz je potreba pracovat s mezivysledkem
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



-- Takto je dobre osetrovat metody
DECLARE
    v_student Student%ROWTYPE;
    
BEGIN
    SELECT * INTO v_student
    FROM Student
    WHERE login = 'abc1223';
    
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