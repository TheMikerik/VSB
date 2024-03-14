-- 3.5
CREATE OR REPLACE TRIGGER TInsertStudent2 BEFORE INSERT ON Student FOR EACH ROW
BEGIN
    :new.login := FGetLogin(:new.lname);
END;


INSERT INTO Student (fname, lname, email, grade, date_of_birth)
VALUES ('Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd'));


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
CREATE OR REPLACE PROCEDURE PAddStudentToCourse(p_student_login Student.login%TYPE, p_course
    v_capacity



--CV 4 - 2
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
        RAISE v_capacity_exceed;
    END IF;
END;