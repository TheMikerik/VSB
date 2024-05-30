-- • SQL S01 L01 ------------------------------------------------------------------------------------
-- o LOWER, UPPER, INITCAP
-- o CONCAT, SUBSTR, LENGTH, INSTR, LPAD, RPAD, TRIM, REPLACE 
-- o Use virtual table DUAL 
SELECT 
    Email,
    LOWER(Email) AS lower_email,
    UPPER(Email) AS upper_email,
    INITCAP(Email) AS initcap_email
FROM Users;

SELECT 
    CONCAT(First_name, ' ', Last_name) AS full_name,
    SUBSTR(Email, 1, 5) AS email_substr,
    LENGTH(Email) AS email_length,
    INSTR(Email, '@') AS at_position
FROM Users;

SELECT 
    LPAD(Name, 10, '*') AS left_padded_name,
    RPAD(Name, 10, '*') AS right_padded_name
FROM Cryptocurrencies;

SELECT 
    TRIM(' ' FROM Email) AS trimmed_email,
    REPLACE(Email, 'email.com', 'example.com') AS replaced_email
FROM Users;

SELECT
    SUBSTR('random text', 1, 6) AS subst
FROM DUAL


-- • SQL S01 L02 ------------------------------------------------------------------------------------
-- o ROUND, TRUNC round for two decimal places, whole thousands MOD 
SELECT 
    Portfolio_ID,
    Title,
    Value,
    ROUND(Value, 2) AS rounded_value,
    TRUNC(Value, -3) AS truncated_to_thousands,
    MOD(Value, 1000) AS remainder_value
FROM Portfolios;


-- • SQL S01 L03 ------------------------------------------------------------------------------------
-- o MONTHS_BETWEEN, ADD_MONTHS, NEXT_DAY, LAST_DAY, ROUND, TRUNC 
-- o System constant SYSDATE
SELECT 
    Transaction_ID,
    Date,
    MONTHS_BETWEEN(SYSDATE, Date) AS months_since_transaction,
    ADD_MONTHS(Date, 6) AS date_plus_6_months,
    NEXT_DAY(Date, 'MONDAY') AS next_monday,
    LAST_DAY(Date) AS last_day_of_month,
    ROUND(Date, 'MONTH') AS rounded_to_month,
    TRUNC(Date, 'MONTH') AS truncated_to_month,
    SYSDATE AS current_date
FROM Transactions;


-- • SQL S02 L01 ------------------------------------------------------------------------------------
-- o TO_CHAR, TO_NUMBER, TO_DATE 
SELECT 
    Transaction_ID,
    Date,
    TO_CHAR(Date, 'DD-MON-YYYY HH24:MI:SS') AS formatted_date
FROM Transactions;

SELECT 
    User_ID,
    Email,
    TO_NUMBER('12345.67') AS converted_number
FROM Users
WHERE User_ID = 1;

SELECT 
    TO_DATE('15-JAN-2023', 'DD-MON-YYYY') AS converted_date
FROM DUAL;

-- • SQL S02 L02 ------------------------------------------------------------------------------------
-- o NVL, NVL2, NULLIF, COALESCE 
SELECT 
    Portfolio_ID,
    Title,
    NVL(Volume, 0) AS volume
FROM Portfolios;

SELECT 
    Portfolio_ID,
    Title,
    NVL2(Volume, Volume, 0) AS volume_value
FROM Portfolios;

SELECT 
    User_ID,
    Email,
    NULLIF(Risk, 3) AS null_if_risk_is_3
FROM Users;

SELECT 
    Portfolio_ID,
    Title,
    COALESCE(Volume, Value, 0) AS non_null_value
FROM Portfolios;


-- • SQL S02 L03 ------------------------------------------------------------------------------------
-- o DECODE, CASE, IF-THEN-ELSE 
SELECT 
    Portfolio_ID,
    Title,
    DECODE(Volume, NULL, 'No Volume', 'Has Volume') AS volume_status
FROM Portfolios;

SELECT 
    Portfolio_ID,
    Title,
    CASE 
        WHEN Volume IS NULL THEN 'No Volume'
        ELSE 'Has Volume'
    END AS volume_status
FROM Portfolios;

-- • SQL S03 L01 ------------------------------------------------------------------------------------
-- o NATURAL JOIN, CROSS JOIN 
SELECT 
    U.User_ID,
    U.Email,
    A.Admin_ID,
    A.First_name,
    A.Last_name
FROM Users U
NATURAL JOIN Admins A;

SELECT 
    U.User_ID,
    U.Email,
    P.Portfolio_ID,
    P.Title
FROM Users U
CROSS JOIN Portfolios P;


-- • SQL S03 L02 ------------------------------------------------------------------------------------
-- o JOIN … USING(atr) 
-- o JOIN .. ON (joining condition) 
SELECT 
    U.User_ID,
    U.Email,
    P.Portfolio_ID,
    P.Title
FROM Users U
JOIN Portfolios P USING (User_ID);

SELECT 
    U.User_ID,
    U.Email,
    T.Transaction_ID,
    T.Volume
FROM Users U
JOIN Portfolios P ON U.User_ID = P.User_ID
JOIN Transactions T ON P.Portfolio_ID = T.Portfolio_ID;


-- • SQL S03 L03 ------------------------------------------------------------------------------------
-- o LEFT OUTER JOIN … ON () 
-- o RIGHT OUTER JOIN … ON () 
-- o FULL OUTER JOIN … ON () 
SELECT 
    U.User_ID,
    U.Email,
    P.Portfolio_ID,
    P.Title
FROM Users U
LEFT OUTER JOIN Portfolios P ON U.User_ID = P.User_ID;

SELECT 
    U.User_ID,
    U.Email,
    P.Portfolio_ID,
    P.Title
FROM Users U
RIGHT OUTER JOIN Portfolios P ON U.User_ID = P.User_ID;

SELECT 
    U.User_ID,
    U.Email,
    P.Portfolio_ID,
    P.Title
FROM Users U
FULL OUTER JOIN Portfolios P ON U.User_ID = P.User_ID;


-- • SQL S03 L04 ------------------------------------------------------------------------------------
-- o Joining 2x of the same table with renaming (link between superiors and subordinates 
-- in one table) 
-- o Hierarchical querying – tree structure of START WITH, CONNECT BY PRIOR, LEVEL 
-- dive 
SELECT 
    A1.Admin_ID AS Superior_ID,
    A1.First_name AS Superior_FirstName,
    A2.Admin_ID AS Subordinate_ID,
    A2.First_name AS Subordinate_FirstName
FROM Admins A1
JOIN Admins A2 ON A1.Admin_ID = A2.User_ID;

SELECT 
    Admin_ID,
    First_name,
    Last_name,
    LEVEL
FROM Admins
START WITH Admin_ID = 1
CONNECT BY PRIOR Admin_ID = User_ID;


-- • SQL S04 L02 ------------------------------------------------------------------------------------
-- o AVG, COUNT, MIN, MAX, SUM, VARIANCE, STDDEV 
SELECT 
    AVG(P.Value) AS Average_Value,
    COUNT(P.Portfolio_ID) AS Total_Portfolios,
    MIN(P.Value) AS Minimum_Value,
    MAX(P.Value) AS Maximum_Value,
    SUM(P.Value) AS Total_Value,
    VARIANCE(P.Value) AS Variance_Value,
    STDDEV(P.Value) AS Stddev_Value
FROM Portfolios P;


-- • SQL S04 L03 ------------------------------------------------------------------------------------
-- o COUNT, COUNT(DISTINCT ), NVL 
-- o Difference between COUNT (*) a COUNT (attribute) 
-- o Why using NVL for aggregation functions 
SELECT 
    Cryptocurrency_ID,
    COUNT(*) AS Total_Transactions,
    COUNT(DISTINCT Portfolio_ID) AS Unique_Portfolios,
    NVL(SUM(Value), 0) AS Total_Value
FROM Transactions
GROUP BY Cryptocurrency_ID;

SELECT 
    Cryptocurrency_ID,
    COUNT(*) AS Total_Transactions,
    COUNT(Value) AS Non_Null_Value_Count
FROM Transactions
GROUP BY Cryptocurrency_ID;

SELECT 
    Cryptocurrency_ID,
    COUNT(*) AS Total_Transactions,
    NVL(SUM(Value), 0) AS Total_Value
FROM Transactions
GROUP BY Cryptocurrency_ID;
-- • SQL S05 L01 ------------------------------------------------------------------------------------
-- o GROUP BY 
-- o HAVING 
SELECT 
    Cryptocurrency_ID,
    COUNT(*) AS Total_Transactions,
    SUM(Value) AS Total_Value
FROM Transactions
GROUP BY Cryptocurrency_ID
HAVING COUNT(*) > 10;

-- • SQL S05 L02 ------------------------------------------------------------------------------------
-- o ROLLUP, CUBE, ROUPING SETS 
SELECT 
    Cryptocurrency_ID,
    Portfolio_ID,
    SUM(Value) AS Total_Value
FROM Transactions
GROUP BY ROLLUP (Cryptocurrency_ID, Portfolio_ID);

SELECT 
    Cryptocurrency_ID,
    Portfolio_ID,
    SUM(Value) AS Total_Value
FROM Transactions
GROUP BY CUBE (Cryptocurrency_ID, Portfolio_ID);

SELECT 
    Cryptocurrency_ID,
    Portfolio_ID,
    SUM(Value) AS Total_Value
FROM Transactions
GROUP BY GROUPING SETS (Cryptocurrency_ID, Portfolio_ID);

-- • SQL S05 L03 ------------------------------------------------------------------------------------
-- o Multiple operations in SQL – UNION, UNION ALL, INTERSECT, MINUS 
-- o ORDER BY for set operations 
SELECT Cryptocurrency_ID, Volume FROM Transactions
UNION
SELECT Cryptocurrency_ID, Value FROM Transactions;

SELECT Cryptocurrency_ID, Volume FROM Transactions
UNION ALL
SELECT Cryptocurrency_ID, Value FROM Transactions;

SELECT Cryptocurrency_ID, Volume FROM Transactions
INTERSECT
SELECT Cryptocurrency_ID, Value FROM Transactions;

SELECT Cryptocurrency_ID, Volume FROM Transactions
MINUS
SELECT Cryptocurrency_ID, Value FROM Transactions;

(SELECT Cryptocurrency_ID, Volume FROM Transactions)
UNION
(SELECT Cryptocurrency_ID, Value FROM Transactions)
ORDER BY Cryptocurrency_ID;


-- • SQL S06 L01 ------------------------------------------------------------------------------------
-- o Nested queries 
-- o Result as a single value 
-- o Multi-column subquery 
-- o EXISTS, NOT EXISTS 
SELECT User_ID, Email
FROM Users
WHERE User_ID IN (
    SELECT DISTINCT User_ID
    FROM Portfolios
);

SELECT AVG(Value) AS Average_Value
FROM Portfolios;

SELECT User_ID, Email
FROM Users
WHERE (User_ID, Email) IN (
    SELECT DISTINCT User_ID, Email
    FROM Admins
);

SELECT User_ID, Email
FROM Users U
WHERE EXISTS (
    SELECT 1
    FROM Portfolios P
    WHERE P.User_ID = U.User_ID
);

SELECT User_ID, Email
FROM Users U
WHERE NOT EXISTS (
    SELECT 1
    FROM Admins A
    WHERE A.User_ID = U.User_ID
);
-- • SQL S06 L02 ------------------------------------------------------------------------------------
-- o One-line subqueries 
SELECT User_ID, Email,
    (SELECT MAX(Value) FROM Portfolios WHERE User_ID = U.User_ID) AS Max_Portfolio_Value
FROM Users U;

-- • SQL S06 L03 ------------------------------------------------------------------------------------
-- o Multi-line subqueries IN, ANY, ALL 
-- o NULL values in subqueries 
SELECT User_ID, Email
FROM Users
WHERE User_ID IN (
    SELECT DISTINCT User_ID
    FROM Portfolios
);

SELECT User_ID, Email
FROM Users
WHERE User_ID = ANY (
    SELECT DISTINCT User_ID
    FROM Portfolios
);

SELECT User_ID, Email
FROM Users
WHERE User_ID = ALL (
    SELECT DISTINCT User_ID
    FROM Portfolios
);

SELECT User_ID, Email
FROM Users
WHERE User_ID IN (
    SELECT DISTINCT User_ID
    FROM Portfolios
) OR User_ID IS NULL;


-- • SQL S06 L04 ------------------------------------------------------------------------------------
-- o WITH .. AS() subquery construction 
WITH UserPortfolios AS (
    SELECT DISTINCT User_ID
    FROM Portfolios
)
SELECT U.User_ID, U.Email
FROM Users U
JOIN UserPortfolios UP ON U.User_ID = UP.User_ID;


-- • SQL S07 L01 ------------------------------------------------------------------------------------
-- o INSERT INTO Tab VALUES() 
-- o INSERT INTo Tab (atr, atr) VALUES() 
-- o INSERT INTO Tab AS SELECT … 
INSERT INTO Users (Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID)
VALUES ('john.doe@email.com', 'JohnPwd_1a2b3c', '123456789', 150000, 3, 2);

INSERT INTO Users (Email, Password)
VALUES ('jane.doe@email.com', 'JanePwd_1a2b3c');

INSERT INTO Users (Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID)
SELECT 'bob.smith@email.com', 'BobPwd_1a2b3c', '987654321', 200000, 2, 3;

-- • SQL S07 L02 ------------------------------------------------------------------------------------
-- o UPDATE Tab SET atr= …. WHERE condition 
-- o DELETE FROM Tab WHERE atr=… 
UPDATE Users
SET Risk = 4
WHERE User_ID = 1;

DELETE FROM Users
WHERE Email = 'jane.doe@email.com';

-- • SQL S07 L03 ------------------------------------------------------------------------------------
-- o DEFAULT, MERGE, Multi-Table Inserts 
CREATE TABLE Example_Table (
    ID INTEGER PRIMARY KEY,
    Name VARCHAR(50) DEFAULT 'Unknown'
);

MERGE INTO Users AS Target
USING Admins AS Source
ON (Target.User_ID = Source.User_ID)
WHEN MATCHED THEN
    UPDATE SET Target.Email = Source.Email
WHEN NOT MATCHED THEN
    INSERT (User_ID, Email)
    VALUES (Source.User_ID, Source.Email);

INSERT ALL 
    INTO Users (Email, Password) VALUES ('test1@email.com', 'Password1')
    INTO Documents (Type, File, Upload_date, User_ID) VALUES ('Test', 'example.pdf', SYSDATE, 1)
SELECT * FROM dual;
-- • SQL S08 L01 ------------------------------------------------------------------------------------
-- o Objects in databases – Tables, Indexes, Constraint, View, Sequence, Synonym 
-- o CREATE, ALTER, DROP, RENAME, TRUNCATE 
-- o CREATE TABLE (atr DAT TYPE, DEFAULT NOT NULL ) 
-- o ORGANIZATION EXTERNAL, TYPE ORACLE_LOADER, DEFAULT DICTIONARY, ACCESS 
-- PARAMETERS, RECORDS DELIMITED BY NEWLINE, FIELDS, LOCATION 
CREATE VIEW User_Details AS
SELECT User_ID, Email, Mobile_number
FROM Users;

CREATE SEQUENCE User_Sequence
START WITH 100
INCREMENT BY 1
NOCACHE
NOCYCLE;

CREATE SYNONYM User_Synonym FOR Users;

ALTER TABLE Users RENAME TO Customers;

ALTER TABLE Customers DROP CONSTRAINT FK_users_currency;

TRUNCATE TABLE Customers;

CREATE TABLE cryptocurrency_data (
    symbol VARCHAR2(10),
    name VARCHAR2(100),
    price_usd NUMBER,
    market_cap_usd NUMBER,
    volume_24h_usd NUMBER
)
ORGANIZATION EXTERNAL (
    TYPE ORACLE_LOADER
    DEFAULT DIRECTORY ext_dir
    ACCESS PARAMETERS (
        RECORDS DELIMITED BY NEWLINE
        FIELDS TERMINATED BY ','
        MISSING FIELD VALUES ARE NULL
        (
            symbol CHAR(10),
            name CHAR(100),
            price_usd FLOAT EXTERNAL TERMINATED BY ',',
            market_cap_usd FLOAT EXTERNAL TERMINATED BY ',',
            volume_24h_usd FLOAT EXTERNAL TERMINATED BY ','
        )
    )
    LOCATION ('cryptocurrency_data.csv')
);


-- • SQL S08 L02 ------------------------------------------------------------------------------------
-- o TIMESTAMP, TIMESTAMP WITH TIME ZONE, TIMESTAMP WITH LOCAL TIMEZONE 
-- o INTERVAL YEAT TO MONTH, INTERVAL DAY TO SECOND 
-- o CHAR, VARCHAR2, CLOB 
-- o about NUMBER 
-- o about BLOB 

SELECT User_ID, Email, CONVERT(VARCHAR, GETDATE(), 20) AS CurrentTimestamp
FROM Users;

SELECT User_ID, Email, SYSDATETIMEOFFSET() AS CurrentTimestampWithTimeZone
FROM Users;

SELECT User_ID, Email, SYSDATETIMEOFFSET() AT TIME ZONE 'UTC' AS CurrentTimestampWithLocalTimeZone
FROM Users;

SELECT User_ID, Email, DATEDIFF(MONTH, SYSDATETIME(), GETDATE()) AS MonthsDifference
FROM Users;

SELECT User_ID, Email, DATEDIFF(SECOND, SYSDATETIME(), GETDATE()) AS SecondsDifference
FROM Users;


SELECT Name, LENGTH(Name) AS Name_Length
FROM Cryptocurrencies;

-- CLOB (Assuming your database supports this)
SELECT Document_ID, Type, CAST(File AS VARCHAR(MAX)) AS File_Content
FROM Documents;

SELECT User_ID, Email, Investment_goals * Risk AS InvestmentRisk
FROM Users;

SELECT Document_ID, Type, File
FROM Documents;

-- • SQL S08 L03 ------------------------------------------------------------------------------------
-- o ALTER TABLE (ADD, MODIFY, DROP), DROP, RENAME 
-- o FLASHBACK TABLE Tab TO BEFORE DROP (view USER_RECYCLEBIN) 
-- o DELETE, TRUNCATE 
-- o COMMENT ON TABLE 
-- o SET UNUSED 

ALTER TABLE Users
ADD NewColumn INT;

ALTER TABLE Users
MODIFY Email VARCHAR(100);

ALTER TABLE Users
DROP COLUMN Mobile_number;

DROP TABLE IF EXISTS TempTable;

ALTER TABLE Users
RENAME TO RenamedUsers;

DELETE FROM Users WHERE User_ID = 1;

TRUNCATE TABLE Documents;

COMMENT ON TABLE Users IS 'This table stores user information.';

ALTER TABLE Users SET UNUSED COLUMN NewColumn;

-- • SQL S10 L01 ------------------------------------------------------------------------------------
-- o CREATE TABLE (NOT NULL AND UNIQUE constraint) 
-- o CREATE TABLE Tab AS SELECT … 
-- o Own vs. system naming CONSTRAINT conditions 
CREATE TABLE idkTest (
    ID INT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Email VARCHAR(100) UNIQUE
);

-- CREATE TABLE Tab AS SELECT … 
CREATE TABLE NewUsers AS
SELECT User_ID, Email
FROM Users;

ALTER TABLE Users
DROP CONSTRAINT FK_users_currency;

ALTER TABLE Users
ADD CONSTRAINT FK_users_currency_custom FOREIGN KEY (Currency_ID) REFERENCES Currencies(Currency_ID);


-- • SQL S10 L02 ------------------------------------------------------------------------------------
-- o CONSTRAINT – NOT NULL, UNIQUE, PRIMARY KEY, FOREIGN KEY (atr REFERENCES 
-- Tab(atr) ), CHECK 
-- o Foreign keys, ON DELETE, ON UPDATE, RESTRICT, CASCADE, etc.
CREATE TABLE ExampleTable (
    ID INT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Email VARCHAR(100) UNIQUE,
    Currency_ID SMALLINT,
    CONSTRAINT FK_Currency FOREIGN KEY (Currency_ID) REFERENCES Currencies(Currency_ID),
    CONSTRAINT CHK_ID CHECK (ID > 0)
);

ALTER TABLE Portfolios
DROP CONSTRAINT FK_portfolios_users;

ALTER TABLE Portfolios
ADD CONSTRAINT FK_portfolios_users FOREIGN KEY (User_ID) REFERENCES Users(User_ID) ON DELETE CASCADE;

ALTER TABLE Portfolios
DROP CONSTRAINT FK_portfolios_users;

ALTER TABLE Portfolios
ADD CONSTRAINT FK_portfolios_users FOREIGN KEY (User_ID) REFERENCES Users(User_ID) ON UPDATE CASCADE;


-- • SQL S10 L03 ------------------------------------------------------------------------------------
-- o about USER_CONSTRAINTS 
SELECT * FROM USER_CONSTRAINTS;

-- • SQL S11 L01 ------------------------------------------------------------------------------------
-- o CREATE VIEW 
-- o about FORCE, NOFORCE 
-- o WITCH CHECK OPTION 
-- o WITH READ ONLY 
-- o about Simple vs. Compex VIEW 

CREATE VIEW UsersViewSimple AS
SELECT User_ID, Email
FROM Users;

CREATE VIEW UsersViewComplex AS
SELECT u.User_ID, u.Email, p.Title
FROM Users u;
JOIN Portfolios p ON u.User_ID = p.User_ID

CREATE VIEW HighRiskUsers AS
SELECT User_ID, Email
FROM Users
WHERE Risk > 3
WITH CHECK OPTION;

CREATE VIEW ReadOnlyUsers AS
SELECT User_ID, Email
FROM Users
WITH READ ONLY;


-- • SQL S11 L03 ------------------------------------------------------------------------------------
-- o INLINE VIEW Subquery in the form of a table SELECT atr FROM (SELECT * FROM Tab) 
-- alt_tab 
SELECT Name 
FROM (SELECT * FROM Users) AS alt_users;


-- • SQL S12 L01 ------------------------------------------------------------------------------------
-- o CREATE SEQUENCE name INCREMENT BY n START WITH m, (NO)MAXVALUE, 
-- (NO)MINVALUE, (NO)CYCLE, (NO)CACHE 
-- o about ALTER SEQUENCE 
CREATE SEQUENCE example_sequence 
INCREMENT BY 1 
START WITH 1 
NOCYCLE 
CACHE 10;

ALTER SEQUENCE example_sequence 
INCREMENT BY 2 
MAXVALUE 1000;


-- • SQL S12 L02 ------------------------------------------------------------------------------------
-- o CREATE INDEX, PRIMARY KEY, UNIQUE KEY, FOREIGN KEY 
ALTER TABLE Users
ADD CONSTRAINT PK_Users PRIMARY KEY (User_ID);

ALTER TABLE Users
ADD CONSTRAINT UK_Users_Email UNIQUE (Email);

ALTER TABLE Transactions
ADD CONSTRAINT FK_Transactions_Portfolios FOREIGN KEY (Portfolio_ID) REFERENCES Portfolios(Portfolio_ID);

-- • SQL S13 L01 ------------------------------------------------------------------------------------
-- o GRANT … ON … TO … PUBLIC 
-- o about REVOKE 
-- o What rights can be assigned to which objects? (ALTER, DELETE, EXECUTE, INDEX, 
-- INSERT, REFERENCES, SELECT, UPDATE) – (TABLE, VIEW, SEQUENCE, PROCEDURE) 
GRANT SELECT ON Users TO PUBLIC;
REVOKE SELECT ON Users FROM username;

-- TABLE: ALTER, DELETE, INDEX, INSERT, REFERENCES, SELECT, UPDATE
-- VIEW: DELETE, INSERT, SELECT, UPDATE
-- SEQUENCE: ALTER, SELECT
-- PROCEDURE: EXECUTE

-- • SQL S13 L03 ------------------------------------------------------------------------------------
-- o Regular expressions 
-- o REGEXP_LIKE, REGEXP_REPLACE, REGEXP_INSTR, REGEXP_SUBSTR, REGEXP_COUNT 

SELECT * FROM Users WHERE REGEXP_LIKE(Email, '.*@.*\.com');

SELECT REGEXP_REPLACE(Email, '@', '.') AS Modified_Email FROM Users;

SELECT REGEXP_INSTR(Email, '@') AS At_Position FROM Users;

SELECT REGEXP_SUBSTR(Email, '[^@]+') AS Username FROM Users;

SELECT REGEXP_COUNT(Email, '@') AS At_Count FROM Users;

-- • SQL S14 L01 ------------------------------------------------------------------------------------
-- o Transactions, COMMIT, ROLLBACK, SAVEPOINT 

SAVEPOINT pre;
BEGIN TRANSACTION;

INSERT INTO Users (Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID)
VALUES ('john.doe@email.com', 'JohnDoePwd123', '123456789', 100000, 2, 1);

INSERT INTO Portfolios (Title, Value, Volume, Wallet_address, User_ID)
VALUES ('John Doe Portfolio', 50000.00, 10.5, '0x123abc', (SELECT User_ID FROM Users WHERE Email = 'john.doe@email.com'));

SELECT * FROM Users WHERE Email = 'john.doe@email.com';
SELECT * FROM Portfolios WHERE User_ID = (SELECT User_ID FROM Users WHERE Email = 'john.doe@email.com');

COMMIT;

ROLLBACK TO pre;


-- • SQL S15 L01 ------------------------------------------------------------------------------------
-- o Alternative join notation without JOIN with join condition in WHERE 
-- o Left and right connection using atrA = atrB (+) 
SELECT *
FROM Users u, Portfolios p
WHERE u.User_ID = p.User_ID;

SELECT *
FROM Users u, Portfolios p
WHERE u.User_ID = p.User_ID(+);