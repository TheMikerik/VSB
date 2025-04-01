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
