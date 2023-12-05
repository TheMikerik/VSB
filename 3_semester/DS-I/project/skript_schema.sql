-------------------------------------------------
CREATE TABLE Cryptocurrencies
    (
     Cryptocurrency_ID INTEGER IDENTITY PRIMARY KEY ,
     Name VARCHAR (20) NOT NULL
    )
GO
-------------------------------------------------
CREATE TABLE Currencies
    (
     Currency_ID SMALLINT IDENTITY PRIMARY KEY ,
     Name VARCHAR (20) NOT NULL
    )
GO
-------------------------------------------------
CREATE TABLE Users
    (
     User_ID INTEGER IDENTITY PRIMARY KEY ,
     Email VARCHAR (64) NOT NULL ,
     Password VARCHAR (64) NOT NULL ,
     Mobile_number INTEGER ,
     Investment_goals INTEGER ,
     Risk SMALLINT ,
     Currency_ID SMALLINT NOT NULL CONSTRAINT FK_users_currency FOREIGN KEY REFERENCES Currencies(Currency_ID)
    )
GO
-------------------------------------------------
CREATE TABLE Admins
    (
     Admin_ID SMALLINT IDENTITY PRIMARY KEY ,
     First_name VARCHAR (30) NOT NULL ,
     Last_name VARCHAR (30) NOT NULL ,
     State VARCHAR (20) NOT NULL ,
     City VARCHAR (30) NOT NULL ,
     Postal_code INTEGER NOT NULL ,
     User_ID INTEGER NOT NULL CONSTRAINT FK_admins_users FOREIGN KEY REFERENCES Users(User_ID)
    )
GO
-------------------------------------------------
CREATE TABLE Vexels
    (
     Trader_ID INTEGER IDENTITY PRIMARY KEY ,
     Location VARCHAR (50) NOT NULL ,
     User_ID INTEGER NOT NULL CONSTRAINT FK_vexels_users FOREIGN KEY REFERENCES Users(User_ID)
    )
GO
-------------------------------------------------
CREATE TABLE Portfolios
    (
     Portfolio_ID SMALLINT IDENTITY PRIMARY KEY ,
     Title VARCHAR (20) NOT NULL ,
     Value FLOAT ,
     Volume FLOAT ,
     Wallet_address VARCHAR (48) ,
     User_ID INTEGER NOT NULL CONSTRAINT FK_portfolios_users FOREIGN KEY REFERENCES Users(User_ID)
    )
GO
-------------------------------------------------
CREATE TABLE Transactions
    (
     Transaction_ID SMALLINT IDENTITY PRIMARY KEY ,
     Volume FLOAT NOT NULL ,
     Value FLOAT ,
     Date DATETIME2 ,
     Portfolio_ID SMALLINT NOT NULL CONSTRAINT FK_transactions_portfolios FOREIGN KEY REFERENCES Portfolios(Portfolio_ID) ,
     Cryptocurrency_ID INTEGER NOT NULL CONSTRAINT FK_transactions_currencies FOREIGN KEY REFERENCES Cryptocurrencies(Cryptocurrency_ID)
    )
GO
-------------------------------------------------
CREATE TABLE P2P_Offers
    (
     Offer_ID INTEGER IDENTITY PRIMARY KEY ,
     Volume FLOAT NOT NULL ,
     Value FLOAT NOT NULL ,
     Place VARCHAR (50) NOT NULL ,
     Status SMALLINT ,
     Negotiable BIT ,
     Cryptocurrency_ID INTEGER NOT NULL CONSTRAINT FK_p2poffer_cryptocurrency FOREIGN KEY REFERENCES Cryptocurrencies(Cryptocurrency_ID) ,
     Trader_ID INTEGER NOT NULL CONSTRAINT FK_p2poffer_vexels FOREIGN KEY REFERENCES Vexels(Trader_ID)
    )
GO
-------------------------------------------------
CREATE TABLE P2P_Transaction
    (
     P2P_Transaction_ID INTEGER IDENTITY PRIMARY KEY ,
     Date DATETIME2 NOT NULL ,
     Offer_ID INTEGER NOT NULL CONSTRAINT FK_p2ptransaction_p2poffer FOREIGN KEY REFERENCES P2P_Offers(Offer_ID)
    )
GO
-------------------------------------------------