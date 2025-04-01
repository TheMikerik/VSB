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

