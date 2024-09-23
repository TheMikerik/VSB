CREATE TABLE Cryptocurrencies
(
    Cryptocurrency_ID INTEGER PRIMARY KEY,
    Name VARCHAR(20) NOT NULL
);

CREATE TABLE Currencies
(
    Currency_ID SMALLINT PRIMARY KEY,
    Name VARCHAR(20) NOT NULL
);

CREATE TABLE Users
(
    User_ID INTEGER PRIMARY KEY,
    Email VARCHAR(64) NOT NULL,
    Password VARCHAR(64) NOT NULL,
    Mobile_number INTEGER,
    Investment_goals INTEGER,
    Risk SMALLINT,
    Currency_ID SMALLINT NOT NULL,
    CONSTRAINT FK_users_currency FOREIGN KEY (Currency_ID) REFERENCES Currencies(Currency_ID)
);

CREATE TABLE Documents
(
    Document_ID INTEGER PRIMARY KEY,
    Type VARCHAR2(50),
    cFile BLOB,
    Upload_date TIMESTAMP,
    User_ID INTEGER,
    FOREIGN KEY (User_ID) REFERENCES Users(User_ID)
);

CREATE TABLE Admins
(
    Admin_ID SMALLINT PRIMARY KEY,
    First_name VARCHAR(30) NOT NULL,
    Last_name VARCHAR(30) NOT NULL,
    State VARCHAR(20) NOT NULL,
    City VARCHAR(30) NOT NULL,
    Postal_code INTEGER NOT NULL,
    User_ID INTEGER NOT NULL,
    CONSTRAINT FK_admins_users FOREIGN KEY (User_ID) REFERENCES Users(User_ID)
);

CREATE TABLE Vexels
(
    Trader_ID INTEGER PRIMARY KEY,
    Location VARCHAR(50) NOT NULL,
    User_ID INTEGER NOT NULL,
    CONSTRAINT FK_vexels_users FOREIGN KEY (User_ID) REFERENCES Users(User_ID)
);

CREATE TABLE Portfolios
(
    Portfolio_ID SMALLINT PRIMARY KEY,
    Title VARCHAR(20) NOT NULL,
    Value FLOAT,
    Volume FLOAT,
    Wallet_address VARCHAR(48),
    User_ID INTEGER NOT NULL,
    CONSTRAINT FK_portfolios_users FOREIGN KEY (User_ID) REFERENCES Users(User_ID)
);

CREATE TABLE Transactions
(
    Transaction_ID SMALLINT PRIMARY KEY,
    Volume FLOAT NOT NULL,
    Value FLOAT,
    cDate TIMESTAMP,
    Portfolio_ID SMALLINT NOT NULL,
    Cryptocurrency_ID INTEGER NOT NULL,
    Parent_Transaction_ID SMALLINT,
    FOREIGN KEY (Portfolio_ID) REFERENCES Portfolios(Portfolio_ID),
    FOREIGN KEY (Cryptocurrency_ID) REFERENCES Cryptocurrencies(Cryptocurrency_ID),
    FOREIGN KEY (Parent_Transaction_ID) REFERENCES Transactions(Transaction_ID)
);



CREATE TABLE P2P_Offers
(
    Offer_ID INTEGER PRIMARY KEY,
    Volume FLOAT NOT NULL,
    Value FLOAT NOT NULL,
    Place VARCHAR(50) NOT NULL,
    Status SMALLINT,
    Negotiable SMALLINT,
    Cryptocurrency_ID INTEGER NOT NULL,
    Trader_ID INTEGER NOT NULL,
    CONSTRAINT FK_p2poffer_cryptocurrency FOREIGN KEY (Cryptocurrency_ID) REFERENCES Cryptocurrencies(Cryptocurrency_ID),
    CONSTRAINT FK_p2poffer_vexels FOREIGN KEY (Trader_ID) REFERENCES Vexels(Trader_ID)
);

CREATE TABLE P2P_Transaction
(
    P2P_Transaction_ID INTEGER PRIMARY KEY,
    cDate TIMESTAMP NOT NULL,
    Offer_ID INTEGER NOT NULL,
    CONSTRAINT FK_p2ptransaction_p2poffer FOREIGN KEY (Offer_ID) REFERENCES P2P_Offers(Offer_ID)
);



INSERT ALL
    INTO Currencies (Currency_ID, Name) VALUES (1, 'CZK')
    INTO Currencies (Currency_ID, Name) VALUES (2, 'USD')
    INTO Currencies (Currency_ID, Name) VALUES (3, 'EUR')
    INTO Currencies (Currency_ID, Name) VALUES (4, 'JPY')
    INTO Currencies (Currency_ID, Name) VALUES (5, 'GBP')
    INTO Currencies (Currency_ID, Name) VALUES (6, 'AUD')
    INTO Currencies (Currency_ID, Name) VALUES (7, 'CAD')
    INTO Currencies (Currency_ID, Name) VALUES (8, 'CHF')
    INTO Currencies (Currency_ID, Name) VALUES (9, 'SEK')
    INTO Currencies (Currency_ID, Name) VALUES (10, 'NOK')
    INTO Currencies (Currency_ID, Name) VALUES (11, 'DKK')
    INTO Currencies (Currency_ID, Name) VALUES (12, 'PLN')
    INTO Currencies (Currency_ID, Name) VALUES (13, 'HUF')
    INTO Currencies (Currency_ID, Name) VALUES (14, 'RUB')
SELECT * FROM dual;


--------------------------------------------
INSERT ALL
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (1, 'BTC')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (2, 'ETH')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (3, 'XRP')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (4, 'LTC')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (5, 'BCH')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (6, 'ADA')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (7, 'DOT')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (8, 'LINK')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (9, 'XLM')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (10, 'BNB')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (11, 'DOGE')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (12, 'USDT')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (13, 'XMR')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (14, 'UNI')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (15, 'EOS')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (16, 'TRX')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (17, 'XTZ')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (18, 'VET')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (19, 'ATOM')
    INTO Cryptocurrencies (Cryptocurrency_ID, Name) VALUES (20, 'SOL')
SELECT * FROM dual;
----------------------------------------------------------------
INSERT ALL
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (1, 'adam.novak@email.com', 'AdamPwd_1a2b3c', '60212233', 1300000, 3, 1)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (2, 'linda.kriz@email.com', 'LindaPwd_4d5e6f', '17711233', 160000, 20, 2)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (3, 'tomas.prochazka@email.com', 'TomasPwd_7g8h9i', '71234567', 11000000, 4, 3)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (4, 'natalie.mareckova@email.com', 'NataliePwd_1j2k3l', '08765432', 140000, 1, 4)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (5, 'martin.svoboda@email.com', 'MartinPwd_4m5n6o', '75577577', 18000, 2, 5)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (6, 'tereza.dvorakova@email.com', 'TerezaPwd_7p8q9r', '60245678', 150000, 4, 6)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (7, 'jiri.horak@email.com', 'JiriPwd_1s2t3u', '70567901', 1200000, 3, 7)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (8, 'barbora.holcova@email.com', 'BarboraPwd_4v5w6x', '73322211', 170000, 5, 8)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (9, 'filip.kovac@email.com', 'FilipPwd_7y8z9a', '21789123', 1900000, 2, 9)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (10, 'lucie.mrazova@email.com', 'LuciePwd_1b2c3d', '60875432', 103000, 4, 10)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (11, 'patrik.juricek@email.com', 'PatrikPwd_4e5f6g', '31245678', 606000, 2, 11)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (12, 'emma.smith@email.com', 'EmmaPwd_7h8i9j', '71234678', 2742000, 3, 12)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (13, 'juan.perez@email.com', 'JuanPwd_1k2l3m', '1234578', 8027000, 4, 1)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (14, 'mario.rossi@email.com', 'MarioPwd_4n5o6p', '12356789', 5412000, 2, 2)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (15, 'yuki.tanaka@email.com', 'YukiPwd_7q8r9s', '8234578', 110000, 5, 3)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (16, 'sophie.dubois@email.com', 'SophiePwd_1t2u3v', '2356789', 140000, 7, 4)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (17, 'ali.khan@email.com', 'AliPwd_4w5x6y', '11234678', 16000, 40, 5)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (18, 'anita.mendoza@email.com', 'AnitaPwd_7z8a9b', '51235678', 13000, 20, 6)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (19, 'vikram.patel@email.com', 'VikramPwd_1c2d3e', '34568901', 70000, 5, 7)
    INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID) VALUES (20, 'mariam.santos@email.com', 'MariamPwd_4f5g6h', '11234678', 15000, 3, 8)
SELECT * FROM dual;

----------------------------------------------------------------
INSERT ALL
    INTO Admins (Admin_ID, First_name, Last_name, State, City, Postal_code, User_ID) VALUES (1, 'Adam', 'Novak', 'Czech Republic', 'Ostrava', 12345, 1)
    INTO Admins (Admin_ID, First_name, Last_name, State, City, Postal_code, User_ID) VALUES (2, 'Mario', 'Rossi', 'California', 'Los Angeles', 90001, 14)
    INTO Admins (Admin_ID, First_name, Last_name, State, City, Postal_code, User_ID) VALUES (3, 'Anita', 'Mendoza', 'Cyprus', 'Limassol', 10001, 18)
    INTO Admins (Admin_ID, First_name, Last_name, State, City, Postal_code, User_ID) VALUES (4, 'Yuki', 'Tanaka', 'Japan', 'Tokio', 77001, 15)
    INTO Admins (Admin_ID, First_name, Last_name, State, City, Postal_code, User_ID) VALUES (5, 'Martin', 'Svoboda', 'Czech Republic', 'Cesky Tesin', 33101, 5)
SELECT * FROM dual;

----------------------------------------------------------------
INSERT ALL
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (1, 'Tech Portfolio', 50000.75, null, '0x6A09F56C7F3F1A7F0D8C4B6A1F1', 1)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (2, 'Finance Portfolio', 75000.25, 15.8, null , 2)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (3, 'Real Investment', 120000.50, 8.2, null, 3)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (4, 'Global Fund', 90000.80, 12.5, '0xC4D2C3B3E2F1A7D8C4B6A1F1', 4)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (5, 'Crypocurrency Mix', 65000.40, 18.7, '0x2F1A7F0D8C4B6A1B6A1F1', 5)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (6, 'Energy Holdings', 80000.60, 14.3, '0x3D1C4D2C3B3E2D8C4B6A1F1', 6)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (7, 'Hehcare Investments', 100000.95, 20.1, null, 7)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (8, 'Development Fund', 110000.20, 10.9, '0xC4D2C1A7F0D8C4B6A1F1', 8)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (9, 'Emerging Portfolio', 95000.70, null, '0xB6A1F10x6E2F1A7F0D81', 9)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (10, 'Disified Holdings', 85000.55, 16.8, '0x7F0D8C4B6A1F10xF1', 10)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (11, 'Technology  Fund', 70000.45, 11.2, '0xE2F1A7F0D8C0D8C4B6A1F1', 11)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (12, 'Goods Investments', 88000.65, null, null, 12)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (13, 'Global Fund', 118000.75, 13.7, '0xB3E2F1A7F0D8F0D8C4B6A1F1', 13)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (14, 'Bioch Holdings', 72000.50, 21.8, '0x2F1A7F0D8C4B6C4B6A1F1', 14)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (15, 'Global Stocks', 105000.90, null, null, 15)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (16, 'Financial Fund', 99000.85, 15.2, '0x9F1A7F0D8C4B6A1F101F1', 16)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (17, 'Tech Opponities', 83000.60, 14.5, null, 17)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (18, 'Energy Holdings', 96000.75, 18.3, '0x6A09F56C7F3DD8C4B6A1F1', 18)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (19, 'Random Holdings', 92000.35, 14.1, '0x7F0D8C4B6A1F10xF1', 6)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (20, 'Azbest Fund', 68000.60, 10.5, '0xE2F1A7F0D8C0D8C4B6A1F1', 6)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (21, 'True Investments', 86000.7, 18.2, null, 6)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (22, 'Local Fund', 115000.90, 12.3, '0xB3E2F1A7F0D8F0D8C4B6A1F1', 2)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (23, 'FinT Holdings', 74000.45, 20.6, '0x2F1A7F0D8C4B6C4B6A1F1', 2)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (24, 'Roll Stocks', 107000.80, null, null, 15)
    INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID) VALUES (25, 'Dropped Fund', 101000.65, 14.9, '0x9F1A7F0D8C4B6A1F101F1', 15)
SELECT * FROM dual;
----------------------------------------------------------------
INSERT ALL
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (1, 0.385, null, TO_TIMESTAMP('2023-01-15T08:30:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 1, 1)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (2, 3.65, null, TO_TIMESTAMP('2023-02-21T14:45:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 4, 3)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (3, 1.25, null, TO_TIMESTAMP('2023-03-10T10:15:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 2, 2)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (4, 2.75, null, null, 3, 4)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (5, 0.95, null, TO_TIMESTAMP('2023-04-05T18:20:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 5, 1)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (6, 4.2, null, TO_TIMESTAMP('2023-05-12T11:30:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 1, 3)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (7, 0.75, null, null, 2, 4)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (8, 2.1, null, TO_TIMESTAMP('2023-06-08T09:00:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 3, 2)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (9, 1.8, null, TO_TIMESTAMP('2023-07-17T16:40:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 4, 1)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (10, 3.3, null, TO_TIMESTAMP('2023-08-23T12:55:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 5, 3)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (11, 0.5, null, null, 1, 2)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (12, 1.65, null, TO_TIMESTAMP('2023-09-30T14:10:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 4, 4)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (13, 2.95, null, TO_TIMESTAMP('2023-10-14T20:05:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 2, 1)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (14, 0.85, null, TO_TIMESTAMP('2023-11-19T13:25:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 3, 3)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (15, 4.5, null, TO_TIMESTAMP('2023-12-03T17:45:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 5, 2)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (16, 1.15, null, null, 1, 4)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (17, 3.8, null, TO_TIMESTAMP('2024-01-07T19:50:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 2, 3)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (18, 0.65, null, TO_TIMESTAMP('2024-02-11T22:15:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 3, 1)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (19, 2.45, null, null, 4, 2)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (20, 1.45, null, null, 8, 2)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (21, 4.05, null, TO_TIMESTAMP('2024-06-30T10:10:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 9, 4)
    INTO Transactions (Transaction_ID, Volume, Value, cDate, Portfolio_ID, Cryptocurrency_ID) VALUES (22, 0.95, null, TO_TIMESTAMP('2024-07-15T18:45:00', 'YYYY-MM-DD"T"HH24:MI:SS'), 10, 1)
SELECT * FROM dual;
----------------------------------------------------------------
INSERT ALL
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (1, 'Dhali', 20)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (2, 'New York', 1)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (3, 'Tokyo', 4)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (4, 'London', 5)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (5, 'Paris', 6)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (6, 'Sydney', 12)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (7, 'Berlin', 10)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (8, 'Los Angeles', 13)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (9, 'Shanghai', 17)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (10, 'Dubai', 19)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (11, 'Singapore', 7)
    INTO Vexels (Trader_ID, Location, User_ID) VALUES (12, 'Prague', 14)
SELECT * FROM dual;
----------------------------------------------------------------
INSERT ALL
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (1, 0.5, 20561.0, 'New York', 3, 0, 1, 1)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (2, 1.8, 4321.0, 'Tokyo', 3, 0, 2, 1)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (3, 3.2, 751.0, 'London', 3, 0, 3, 3)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (4, 1.0, 782.0, 'Paris', 3, 0, 1, 4)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (5, 4.5, 242.0, 'Sydney', 2, 0, 5, 5)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (6, 2.0, 78224.0, 'Berlin', 2, 1, 1, 6)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (7, 3.8, 78.0, 'Los Angeles', 2, 1, 1, 1)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (8, 1.2, 34.0, 'Shanghai', 1, 0, 3, 8)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (9, 2.7, 7375.0, 'Dubai', 1, 1, 4, 9)
    INTO P2P_Offers (Offer_ID, Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID) VALUES (10, 3.5, 5200.0, 'Singapore', 1, 1, 5, 1)
SELECT * FROM dual;
----------------------------------------------------------------
INSERT ALL
    INTO P2P_Transaction (P2P_Transaction_ID, cDate, Offer_ID)VALUES (1, TIMESTAMP '2019-01-15 08:30:00', 1)
    INTO P2P_Transaction (P2P_Transaction_ID, cDate, Offer_ID)VALUES (2, TIMESTAMP '2021-02-21 14:45:00', 2)
    INTO P2P_Transaction (P2P_Transaction_ID, cDate, Offer_ID)VALUES (3, TIMESTAMP '2022-03-10 10:15:00', 3)
    INTO P2P_Transaction (P2P_Transaction_ID, cDate, Offer_ID)VALUES (4, TIMESTAMP '2023-11-19 13:25:00', 4)
SELECT *FROM dual;
----------------------------------------------------------------


























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
    User_ID || ': ' || Email AS IdEmail,
    SUBSTR(Email, 1, 5) AS email_substr,
    LENGTH(Email) AS email_length,
    INSTR(Email, '@') AS at_position
FROM Users;


SELECT
    LPAD(Name, 4, '*') AS left_padded_name,
    RPAD(Name, 4, '*') AS right_padded_name
FROM Cryptocurrencies;

SELECT
    TRIM(' ' FROM Email) AS trimmed_email,
    REPLACE(Email, 'email.com', 'x.com') AS replaced_email
FROM Users;

SELECT
    SUBSTR('random text', 1, 6) AS subst
FROM DUAL;


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
    cDate,
    MONTHS_BETWEEN(SYSDATE, cDate) AS months_since_transaction,
    ADD_MONTHS(cDate, 6) AS date_plus_6_months,
    NEXT_DAY(cDate, 'MONDAY') AS next_monday,
    LAST_DAY(cDate) AS last_day_of_month,
    ROUND(cDate, 'MM') AS rounded_to_month,
    TRUNC(cDate, 'MONTH') AS truncated_to_month,
    SYSDATE AS current_date
FROM Transactions;



-- • SQL S02 L01 ------------------------------------------------------------------------------------
-- o TO_CHAR, TO_NUMBER, TO_DATE
SELECT
    Transaction_ID,
    cDate,
    TO_CHAR(cDate, 'DD-MON-YYYY HH24:MI:SS') AS formatted_date
FROM Transactions;

SELECT
    User_ID,
    Email,
    TO_NUMBER('12345') AS converted_number
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
JOIN Admins A ON U.User_ID = A.User_ID;


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
    User_ID,
    Email,
    Portfolio_ID,
    Title
FROM Users
JOIN Portfolios USING (User_ID);

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
INSERT INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID)
VALUES (30, 'john.doe@email.com', 'JohnPwd_1a2b3c', '123456789', 150000, 3, 2);

INSERT INTO Currencies (Currency_ID, NAME)
VALUES (30, 'ISL');

INSERT INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID)
SELECT 31, 'bob.smith@email.com', 'BobPwd_1a2b3c', '987654321', 200000, 2, 3 FROM DUAL;

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

-- MERGE INTO Users Target
-- USING Admins Source
-- ON (Target.User_ID = Source.User_ID)
-- WHEN MATCHED THEN
--     UPDATE SET Target.Email = Source.Email
-- WHEN NOT MATCHED THEN
--     INSERT (User_ID, Email)
--     VALUES (Source.User_ID, Source.Email);



INSERT ALL
    INTO Users (User_ID, Email, Password, Currency_ID) VALUES (32, 'test1@email.com', 'Password1', 3)
    INTO Currencies (Currency_ID, Name) VALUES (31, 'IDK')
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
ALTER TABLE Customers RENAME TO Users;

ALTER TABLE Customers DROP CONSTRAINT FK_users_currency;

TRUNCATE TABLE Currencies;

CREATE DIRECTORY ext_dir AS '/test';

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

SELECT
    Transaction_ID,
    Volume,
    CURRENT_TIMESTAMP AS CurrentTimestamp,
    SYSTIMESTAMP AS CurrentTimestampWithTimeZone,
    SYS_EXTRACT_UTC(SYSTIMESTAMP) AS CurrentTimestampWithLocalTimeZone,
    MONTHS_BETWEEN(SYSDATE, cDate) AS MonthsDifference,
    (SYSDATE - cDate) * 24 * 60 * 60 AS SecondsDifference
FROM
    TRANSACTIONS;



SELECT Name, LENGTH(Name) AS Name_Length
FROM Cryptocurrencies;

-- CLOB (Assuming your database supports this)
SELECT Document_ID, Type, DBMS_LOB.SUBSTR(cFile, 4000, 1) AS File_Content
FROM Documents;


SELECT User_ID, Email, Investment_goals * Risk AS InvestmentRisk
FROM Users;

-- • SQL S08 L03 ------------------------------------------------------------------------------------
-- o ALTER TABLE (ADD, MODIFY, DROP), DROP, RENAME
-- o FLASHBACK TABLE Tab TO BEFORE DROP (view USER_RECYCLEBIN)
-- o DELETE, TRUNCATE
-- o COMMENT ON TABLE
-- o SET UNUSED

ALTER TABLE Users
ADD NewColumn INT;

SELECT *
from Users;

ALTER TABLE Users
MODIFY Email VARCHAR(100);

ALTER TABLE Users
DROP COLUMN Mobile_number;

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
FROM Users u
JOIN Portfolios p ON u.User_ID = p.User_ID;

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
SELECT Email
FROM (SELECT * FROM Users) alt_users;


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
REVOKE SELECT ON Users FROM RUC0066;

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

SELECT REGEXP_COUNT(Email, 'a') AS At_Count FROM Users;

-- • SQL S14 L01 ------------------------------------------------------------------------------------
-- o Transactions, COMMIT, ROLLBACK, SAVEPOINT

SAVEPOINT pre;
BEGIN
    INSERT INTO Users (User_ID, Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID)
    VALUES (40, 'john.dosse@email.com', 'JohnDoePwd123', '123456789', 100000, 2, 1);

    INSERT INTO Portfolios (Portfolio_ID, Title, Value, Volume, Wallet_address, User_ID)
    VALUES (40, 'John Doe Portfolio', 50000.00, 10.5, '0x123abc', (SELECT User_ID FROM Users WHERE Email = 'john.doe@email.com'));

    COMMIT;

EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK TO pre;
        RAISE;
END;



-- • SQL S15 L01 ------------------------------------------------------------------------------------
-- o Alternative join notation without JOIN with join condition in WHERE
-- o Left and right connection using atrA = atrB (+)
SELECT *
FROM Users u, Portfolios p
WHERE u.User_ID = p.User_ID;

SELECT *
FROM Users u, Portfolios p
WHERE u.User_ID = p.User_ID(+);