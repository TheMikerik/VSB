/*1;1;4;Vypiš jména kryptoměn, které mají název delší než 3 znaky*/
SELECT name, len(Name) as length
FROM Cryptocurrencies
where len(Name) > 3

/*1;2;10;Vypiš všechny transakce a seřaď je sestupně*/
SELECT *
FROM P2P_Offers
ORDER BY VALUE DESC

/*1;3;1;Vypiš transakci s největším objemem*/
SELECT MAX(Value) as MaxValue
FROM P2P_Offers

/*1;4;20;Vypiš údaje o všech uživatelích a seřaď je vzestupně dle délky jejich emailu*/
SELECT *
FROM Users
ORDER BY len(Email)



/*2;1;3;Vypiš ID nabídky, její objem, místo, status, ID kryptoměny a název kryptoměny kde ID kryptoměny bude 1 nebo 2 a zároveň nabídka bude bez možnosti smlouvání*/
SELECT o.Offer_ID, o.Volume, o.Place, o.Status, o.Cryptocurrency_ID, c.Name
FROM P2P_Offers o
JOIN dbo.Cryptocurrencies c on o.Cryptocurrency_ID = c.Cryptocurrency_ID
WHERE (c.Cryptocurrency_ID = 1 OR c.Cryptocurrency_ID = 2) AND o.Negotiable = 'false'

/*2;2;18;Vypiš údaje o portfoliích, které mají přidané sledování jakékoliv kryptoměnové adresy*/
SELECT *
FROM Portfolios
WHERE Wallet_address IS NOT NULL

/*2;3;13;Vypiš údaje o portfoliích, které obsahují v názvu výraz "fund" a obsahují transakce s ETH nebo s BTC*/
SELECT *
FROM Portfolios P
JOIN dbo.Transactions T on P.Portfolio_ID = T.Portfolio_ID
JOIN dbo.Cryptocurrencies C on T.Cryptocurrency_ID = C.Cryptocurrency_ID
WHERE title LIKE '%fund%' AND
      C.Name = 'ETH' OR C.Name = 'BTC'

/*2;4;1;Vypis udaje o nejstarsi transakci (datum, druh kryptomeny, objem a misto provedeni transakce) a o vexlakovi (email a lokaci), ktery ji uzavrel*/
SELECT t.Date, c.Name, o.Volume, o.Place, u.email, v.Location
FROM Vexels V
JOIN dbo.Users U on U.User_ID = V.User_ID
JOIN dbo.P2P_Offers o ON V.Trader_ID = o.Trader_ID
JOIN dbo.P2P_Transaction t ON V.Trader_ID = t.Trader_ID
JOIN dbo.Cryptocurrencies C on C.Cryptocurrency_ID = o.Cryptocurrency_ID
WHERE o.Offer_ID = t.Trader_ID AND
      t.Date = ALL (SELECT MIN(Date) FROM dbo.P2P_Transaction);        ------------------------          o.Offer_ID = t.Trader_ID MISTAKE traderID=OIFFERID