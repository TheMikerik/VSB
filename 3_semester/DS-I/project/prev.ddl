
CREATE TABLE Admins 
    (
     Admin_ID SMALLINT NOT NULL , 
     First_name VARCHAR (30) NOT NULL , 
     Last_name VARCHAR (30) NOT NULL , 
     State VARCHAR (20) NOT NULL , 
     City VARCHAR (30) NOT NULL , 
     Postal_code INTEGER NOT NULL , 
     Users_User_ID INTEGER NOT NULL 
    )
GO 

    


CREATE UNIQUE NONCLUSTERED INDEX 
    Admins__IDX ON Admins 
    ( 
     Users_User_ID 
    ) 
GO

ALTER TABLE Admins ADD CONSTRAINT Admins_PK PRIMARY KEY CLUSTERED (Admin_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE Cryptocurrencies 
    (
     Cryptocurrency_ID INTEGER NOT NULL , 
     Name VARCHAR (20) NOT NULL 
    )
GO

ALTER TABLE Cryptocurrencies ADD CONSTRAINT Cryptocurrencies_PK PRIMARY KEY CLUSTERED (Cryptocurrency_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE Currencies 
    (
     Currency_ID SMALLINT NOT NULL , 
     Name VARCHAR (20) NOT NULL 
    )
GO

ALTER TABLE Currencies ADD CONSTRAINT Currencies_PK PRIMARY KEY CLUSTERED (Currency_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE P2P_Offers 
    (
     Offer_ID INTEGER NOT NULL , 
     Cryptocurrency_ID SMALLINT NOT NULL , 
     Volume FLOAT NOT NULL , 
     Value FLOAT NOT NULL , 
     Place VARCHAR (50) NOT NULL , 
     Status SMALLINT , 
     Negotiable BIT , 
     Cryptocurrencies_Cryptocurrency_ID INTEGER NOT NULL , 
     Vexels_Trader_ID INTEGER NOT NULL 
    )
GO

ALTER TABLE P2P_Offers ADD CONSTRAINT P2P_Offers_PK PRIMARY KEY CLUSTERED (Offer_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE P2P_Transaction 
    (
     P2P_Transaction_ID INTEGER NOT NULL , 
     Date DATETIME2 NOT NULL , 
     P2P_Offers_Offer_ID INTEGER NOT NULL 
    )
GO 

    


CREATE UNIQUE NONCLUSTERED INDEX 
    P2P_Transaction__IDX ON P2P_Transaction 
    ( 
     P2P_Offers_Offer_ID 
    ) 
GO

ALTER TABLE P2P_Transaction ADD CONSTRAINT P2P_Transaction_PK PRIMARY KEY CLUSTERED (P2P_Transaction_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE Portfolios 
    (
     Portfolio_ID SMALLINT NOT NULL , 
     Title VARCHAR (20) NOT NULL , 
     Value FLOAT , 
     Volume FLOAT , 
     Wallet_address VARCHAR (48) , 
     Users_User_ID INTEGER NOT NULL 
    )
GO

ALTER TABLE Portfolios ADD CONSTRAINT Portfolios_PK PRIMARY KEY CLUSTERED (Portfolio_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE Transactions 
    (
     Transaction_ID SMALLINT NOT NULL , 
     Volume FLOAT NOT NULL , 
     Value FLOAT , 
     Date DATETIME2 , 
     Portfolios_Portfolio_ID SMALLINT NOT NULL , 
     Cryptocurrencies_Cryptocurrency_ID INTEGER NOT NULL 
    )
GO

ALTER TABLE Transactions ADD CONSTRAINT Transactions_PK PRIMARY KEY CLUSTERED (Transaction_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE Users 
    (
     User_ID INTEGER NOT NULL , 
     Email VARCHAR (64) NOT NULL , 
     Password VARCHAR (64) NOT NULL , 
     Mobile_number INTEGER , 
     Investment_goals INTEGER , 
     Risk SMALLINT , 
     Currencies_Currency_ID SMALLINT NOT NULL 
    )
GO

ALTER TABLE Users ADD CONSTRAINT Users_PK PRIMARY KEY CLUSTERED (User_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

CREATE TABLE Vexels 
    (
     Trader_ID INTEGER NOT NULL , 
     Location VARCHAR (50) NOT NULL , 
     Users_User_ID INTEGER NOT NULL 
    )
GO 

    


CREATE UNIQUE NONCLUSTERED INDEX 
    Vexels__IDX ON Vexels 
    ( 
     Users_User_ID 
    ) 
GO

ALTER TABLE Vexels ADD CONSTRAINT Vexels_PK PRIMARY KEY CLUSTERED (Trader_ID)
     WITH (
     ALLOW_PAGE_LOCKS = ON , 
     ALLOW_ROW_LOCKS = ON )
GO

ALTER TABLE Admins 
    ADD CONSTRAINT Admins_Users_FK FOREIGN KEY 
    ( 
     Users_User_ID
    ) 
    REFERENCES Users 
    ( 
     User_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE P2P_Offers 
    ADD CONSTRAINT P2P_Offers_Cryptocurrencies_FK FOREIGN KEY 
    ( 
     Cryptocurrencies_Cryptocurrency_ID
    ) 
    REFERENCES Cryptocurrencies 
    ( 
     Cryptocurrency_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE P2P_Offers 
    ADD CONSTRAINT P2P_Offers_Vexels_FK FOREIGN KEY 
    ( 
     Vexels_Trader_ID
    ) 
    REFERENCES Vexels 
    ( 
     Trader_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE P2P_Transaction 
    ADD CONSTRAINT P2P_Transaction_P2P_Offers_FK FOREIGN KEY 
    ( 
     P2P_Offers_Offer_ID
    ) 
    REFERENCES P2P_Offers 
    ( 
     Offer_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE Portfolios 
    ADD CONSTRAINT Portfolios_Users_FK FOREIGN KEY 
    ( 
     Users_User_ID
    ) 
    REFERENCES Users 
    ( 
     User_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE Transactions 
    ADD CONSTRAINT Transactions_Cryptocurrencies_FK FOREIGN KEY 
    ( 
     Cryptocurrencies_Cryptocurrency_ID
    ) 
    REFERENCES Cryptocurrencies 
    ( 
     Cryptocurrency_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE Transactions 
    ADD CONSTRAINT Transactions_Portfolios_FK FOREIGN KEY 
    ( 
     Portfolios_Portfolio_ID
    ) 
    REFERENCES Portfolios 
    ( 
     Portfolio_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE Users 
    ADD CONSTRAINT Users_Currencies_FK FOREIGN KEY 
    ( 
     Currencies_Currency_ID
    ) 
    REFERENCES Currencies 
    ( 
     Currency_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO

ALTER TABLE Vexels 
    ADD CONSTRAINT Vexels_Users_FK FOREIGN KEY 
    ( 
     Users_User_ID
    ) 
    REFERENCES Users 
    ( 
     User_ID 
    ) 
    ON DELETE NO ACTION 
    ON UPDATE NO ACTION 
GO



-- Oracle SQL Developer Data Modeler Summary Report: 
-- 
-- CREATE TABLE                             9
-- CREATE INDEX                             3
-- ALTER TABLE                             18
-- CREATE VIEW                              0
-- ALTER VIEW                               0
-- CREATE PACKAGE                           0
-- CREATE PACKAGE BODY                      0
-- CREATE PROCEDURE                         0
-- CREATE FUNCTION                          0
-- CREATE TRIGGER                           0
-- ALTER TRIGGER                            0
-- CREATE DATABASE                          0
-- CREATE DEFAULT                           0
-- CREATE INDEX ON VIEW                     0
-- CREATE ROLLBACK SEGMENT                  0
-- CREATE ROLE                              0
-- CREATE RULE                              0
-- CREATE SCHEMA                            0
-- CREATE SEQUENCE                          0
-- CREATE PARTITION FUNCTION                0
-- CREATE PARTITION SCHEME                  0
-- 
-- DROP DATABASE                            0
-- 
-- ERRORS                                   0
-- WARNINGS                                 0
