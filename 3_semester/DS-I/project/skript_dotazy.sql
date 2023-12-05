/*1;1;4;Vypiš jména kryptoměn, které mají název delší než 3 znaky*/
SELECT name, len(Name) as length
FROM Cryptocurrencies
where len(Name) > 3

/*1;2;10;Vypiš všechny transakce a seřaď je sestupně dle atributu value*/
SELECT o.Offer_ID, o.Volume, o.Value, o.Place
FROM P2P_Offers o
ORDER BY o.value DESC

/*1;3;1;Vypiš transakci s největším objemem*/
SELECT MAX(Value) as MaxValue
FROM P2P_Offers

/*1;4;20;Vypiš údaje o všech uživatelích a seřaď je vzestupně dle délky jejich emailu*/
SELECT u.User_ID, u.Email, u.Mobile_number, u.Currency_ID
FROM Users u
ORDER BY len(Email)




/*2;1;3;Vypiš ID nabídky, její objem, místo, status, ID kryptoměny a název kryptoměny kde ID kryptoměny bude 1 nebo 2 a zároveň nabídka bude bez možnosti smlouvání*/
SELECT o.Offer_ID, o.Volume, o.Place, o.Status, o.Cryptocurrency_ID, c.Name
FROM P2P_Offers o
JOIN dbo.Cryptocurrencies c on o.Cryptocurrency_ID = c.Cryptocurrency_ID
WHERE (c.Cryptocurrency_ID = 1 OR c.Cryptocurrency_ID = 2) AND o.Negotiable = 'false'

/*2;2;18;Vypiš údaje o portfoliích, které mají přidané sledování jakékoliv kryptoměnové adresy*/
SELECT p.Portfolio_ID, p.Title, p.Wallet_address
FROM Portfolios p
WHERE p.Wallet_address IS NOT NULL

/*2;3;13;Vypiš údaje o portfoliích, které obsahují v názvu výraz "fund" a obsahují transakce s ETH nebo s BTC*/
SELECT p.Portfolio_ID, p.Title, c.Name
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
JOIN dbo.P2P_Transaction t ON o.Offer_ID = t.Offer_ID
JOIN dbo.Cryptocurrencies C on C.Cryptocurrency_ID = o.Cryptocurrency_ID
WHERE o.Offer_ID = t.Offer_ID AND
      t.Date = (SELECT MIN(Date) FROM dbo.P2P_Transaction);




/*3;1;6;Vypiste transakce, ktere neobsahuji kryptomenu BTC ani ETH a portfolio, ke kteremu jsou prirazene patri jakemukoliv adminovi s pouzitim in */
select t.Transaction_ID, t.Volume, t.Cryptocurrency_ID
from Transactions T
where t.Portfolio_ID in (
        select P.Portfolio_ID
        from Admins a
        join dbo.Portfolios P on a.User_ID = P.User_ID
      )
      AND T.Cryptocurrency_ID not in (
        select Cryptocurrency_ID
        from Cryptocurrencies
        where name = 'BTC' OR name = 'ETH'
      )

/*3;2;6;Vypiste transakce, ktere neobsahuji kryptomenu BTC ani ETH a portfolio, ke kteremu jsou prirazene patri jakemukoliv adminovi s pouzitim exists */
select t.Transaction_ID, t.Volume, t.Cryptocurrency_ID
from Transactions t
where exists(
        select 1
        from Admins a
        join dbo.Portfolios P on a.User_ID = P.User_ID
        where P.Portfolio_ID = t.Portfolio_ID
    ) AND not exists(
        select 1
        from Cryptocurrencies c
        where (name = 'BTC' OR name = 'ETH') AND c.Cryptocurrency_ID = t.Cryptocurrency_ID
    )

/*3;3;6;Vypiste transakce, ktere neobsahuji kryptomenu BTC ani ETH a portfolio, ke kteremu jsou prirazene patri jakemukoliv adminovi s pouzitim intersect */
select t.Transaction_ID, t.Volume, t.Cryptocurrency_ID
from Transactions t
join dbo.Portfolios P on P.Portfolio_ID = t.Portfolio_ID
join dbo.Admins A on P.User_ID = A.User_ID

intersect

select t.Transaction_ID, t.Volume, t.Cryptocurrency_ID
from Transactions t
join dbo.Cryptocurrencies C on C.Cryptocurrency_ID = t.Cryptocurrency_ID
where c.Name != 'BTC' AND c.Name != 'ETH'

/*3;4;6;Vypiste transakce, ktere neobsahuji kryptomenu BTC ani ETH a portfolio, ke kteremu jsou prirazene patri jakemukoliv adminovi s pouzitim expect */
select t.Transaction_ID, t.Volume, t.Cryptocurrency_ID
from Transactions t
join dbo.Portfolios P on P.Portfolio_ID = t.Portfolio_ID
join dbo.Admins A on P.User_ID = A.User_ID
join dbo.Cryptocurrencies C2 on t.Cryptocurrency_ID = C2.Cryptocurrency_ID

except

select t.Transaction_ID, t.Volume, t.Cryptocurrency_ID
from Transactions t
join dbo.Cryptocurrencies C on C.Cryptocurrency_ID = t.Cryptocurrency_ID
where c.Name = 'BTC' OR c.Name = 'ETH'





/*4;1;4; Pro kazdou kryptomenu vypis jeji prumerny objem v transakcich. Pokud se dana kryptomena neobjevuje v zadne transakci, tak ji nevypisuj*/
select c.Cryptocurrency_ID, c.Name, AVG(Volume) as prumerna_transakce
from Cryptocurrencies c
join dbo.Transactions T on c.Cryptocurrency_ID = T.Cryptocurrency_ID
group by c.Cryptocurrency_ID, c.Name
order by c.Cryptocurrency_ID

/*4;2;20;Pro kazdeho uzivatele vypis pocet jeho transacki, ktere ma zaznamenane v portfoliich*/
select u.User_ID, u.Email, COUNT(T.Transaction_ID) as transakce
from Users u
left join dbo.Portfolios P on u.User_ID = P.User_ID
left join dbo.Transactions T on P.Portfolio_ID = T.Portfolio_ID
group by u.User_ID, u.Email
order by transakce DESC

/*4;3;20;Pro kazdeho uzivatele vypis hodnotu vsech jeho portfolii */
select
    u.User_ID,
    case when sum(p.Value)
        is null then 0
        ELSE sum(p.Value) END
    as hodnota_portfolii
from Users u
left join dbo.Portfolios P on u.User_ID = P.User_ID
group by u.User_ID

/*4;4;5;Vypis vsechny uzivatele, kteri maji vice nez 1 portfolio */
select u.User_ID, u.Email
from Users u
where u.User_ID in (
    select p.User_ID
    from Portfolios p
    group by p.User_ID
    having count(*) > 1
    )





/*5;1;3;  Pro menu CZK, JPY a PLN vypis kolik useru je ma nastavene jako primarni menu  */
select u.Currency_ID, count(*) as primarni_mena
from Users u
join dbo.Currencies C on C.Currency_ID = u.Currency_ID
where c.Name in ('CZK', 'JPY', 'PLN')
group by u.Currency_ID

/*5;2;3;  Pro menu CZK, JPY a PLN vypis kolik useru je ma nastavene jako primarni menu  */
select u.Currency_ID, count(*) as primarni_mena
from Users u
where u.Currency_ID in (
        select c2.Currency_ID
        from Currencies c2
        where c2.Name in ('CZK', 'JPY', 'PLN')
    )
group by u.Currency_ID

/*5;3;9;  Vypocitej prumernou cenu transakce pripsanou do portfolia, na ktere neni napojena penezenka*/
select p.Portfolio_ID, p.Title, AVG(t.Volume) as prumerna_transakce
from Portfolios p
left join dbo.Transactions T on p.Portfolio_ID = T.Portfolio_ID
where p.Wallet_address is null
group by p.Portfolio_ID, p.Title
order by prumerna_transakce DESC

/*5;4;3; Vypis nejstarsi uzavrenou nabidku pro kazdou vexlacku (email obsahuje '%ova@%'). Pokud doposud neuzavrela zadnou nabidku, ponechte ve vysledku null */
select
    v.Trader_ID,
    MIN(t.Date) as nejstarsi_uzavrena,
    u.Email
from Vexels v
join dbo.Users U on U.User_ID = v.User_ID
left join dbo.P2P_Offers o on v.Trader_ID = o.Trader_ID
left join dbo.P2P_Transaction t on o.Offer_ID = t.Offer_ID
where u.Email like '%ova@%'
group by v.Trader_ID, u.Email




/*6;1;15;  Pro kryptomenove portfolia obsahujici nazev 'holdings' nebo 'fund' vypiste pocet transakci, ktere se v nich vyskuji a z toho pocet transakci s BTC. Vysledek seradte sestupne dle poctu transakci*/
select p.Portfolio_ID, p.Title, (
        select count(*)
        from Transactions t
        where t.Portfolio_ID = p.Portfolio_ID
    ) as pocet_transakci, (
        select count(*)
        from Transactions t
        join dbo.Cryptocurrencies C on C.Cryptocurrency_ID = t.Cryptocurrency_ID
        where c.Cryptocurrency_ID in (
                select cr.Cryptocurrency_ID
                from Cryptocurrencies cr
                where cr.Name = 'BTC'
            ) AND t.Portfolio_ID = p.Portfolio_ID
    ) as BTC_Transakce
from Portfolios p
where p.Title like '%holdings%' OR p.Title like '%fund%'
order by pocet_transakci DESC

/*6;2;1; U admina, ktery je zaroven veden jako vexlak, vypis pocet vsech jeho aktivnich i uzavrenych nabidek a datum nejstarsi uzavrene nabidky*/
select
    o.Trader_ID,
    a.Admin_ID,
    concat(a.First_name + ' ', a.Last_name) as jmeno, (
        select count(*)
        from P2P_Offers p2
        where p2.Trader_ID = o.Trader_ID
    ) as pocet_nabidek, (
        select min(t.Date)
        from P2P_Offers o2
        join dbo.P2P_Transaction t on o2.Offer_ID = t.Offer_ID
        where o2.Trader_ID = o.Trader_ID
    ) as nejstarsi_uzavrena
from Admins a
join dbo.Vexels V on a.User_ID = V.User_ID
join dbo.P2P_Offers o on V.Trader_ID = o.Trader_ID
group by o.Trader_ID, a.Admin_ID, concat(a.First_name + ' ', a.Last_name)