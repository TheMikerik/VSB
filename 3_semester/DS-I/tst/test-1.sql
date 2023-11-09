-------------------------------------------
--        First lecture
-------------------------------------------
-- https://dbedu.cs.vsb.cz/cs/Files/GetFiles/2020-2021/DS%20I/ds1_sbirka_s_resenim.pdf
-------------------------------------------

-- 7
select *
from
    film
where
    film.length > 50 AND
    film.rental_duration in (3, 5)

-- 8
select title
from
    film
where
    (film.title LIKE '%RAINBOW%' OR title LIKE 'TEXAS%') AND
    film.length > 70

-- 9
select
    title
from
    film
where
    description like '%And%' AND
    length between 80 and 90 AND
    rental_duration % 2 = 1

-- 10
select
    distinct special_features
from
    film
where
    replacement_cost between 14 and 16
order by
    special_features

-- 11
select
    *
from
    film
where
    rental_duration < 4 AND rating != 'PG' OR
    rental_duration >= 4 and rating = 'PG'

-- 12
select
    *
from
    address
where
    postal_code is not null

-- 13
select
    customer_id
from
    rental
where
    return_date is null

-- 14
select
    payment_id,
    YEAR(payment_date) as rok,
    MONTH(payment_date) as mesic,
    DAY(payment_date) as den
from
    payment

-- 15
select
    *
from
    film
where
    LEN(title) != 20

-- 16
select
    rental_id,
    DATEDIFF(minute, rental_date, return_date) as minuty
from
    rental
where
    return_date is not null

-- 17
select
    customer_id,
    CONCAT(first_name,' ' ,last_name) as fullname
from
    customer

-- 18
select
    address,
    coalesce(postal_code, 'xxx') as psc
    --COALESCE: Replace NULL values with selected variable
from
    address

-- 19
select
    rental_id,
    CONCAT(rental_date, ' - ', return_date)
from
    rental
where
    return_date is not null

-- 20
select
    rental_id,
    CONCAT(rental_date, coalesce(' - ' + cast(return_date as varchar), ''))
from
    rental

-- 21
select
    count(*) as no_film
from
    film

-- 22
select
    count(distinct rating)
from
    film

-- 23
select
    count(*),
    count(postal_code) as psc,
    count(distinct postal_code) as nopsc
from
    address

-- 24
select
    MAX(length) as maxln,
    MIN(length) as minln,
    AVG(cast(length as float)) as avgln
from
    film

-- 25
select
    count(*) as pocet,
    sum(amount) as soucet
from
    payment
where
    year(payment_date) = 2005

-- 26
select
    sum(len(title))
from
    film


-------------------------------------------
--        Second lecture
-------------------------------------------
-- 1
select
    *
from
    city
join country c on c.country_id = city.country_id

-- 2
select f.title, l.name
from film f
join language l on f.language_id = l.language_id

-- 3
select r.rental_id, CONCAT(c.first_name, ' ', c.last_name)
from rental r
join customer c on r.customer_id = c.customer_id
where c.last_name like 'SIMPSON'

-- 4
select
    address
from
    address a
join customer c on a.address_id = c.address_id
where c.last_name like 'SIMPSON'

-- 5
select
    distinct c.first_name, c.last_name, a.address, ci.city
from customer c
join address a on c.address_id = a.address_id
join city ci on a.city_id = ci.city_id

-- 6
select
    distinct c.first_name, c.last_name, ci.city
from customer c
join address a on c.address_id = a.address_id
join city ci on a.city_id = ci.city_id

-- 7
select
    r.rental_id,
    CONCAT(sf.first_name, ' ', sf.last_name) as staff,
    CONCAT(c.first_name, ' ', c.last_name) as customer,
    f.title
from film f
    join inventory i on f.film_id = i.film_id
    join rental r on i.inventory_id = r.inventory_id
    join customer c on r.customer_id = c.customer_id
    join store s on i.store_id = s.store_id
    join staff sf on s.store_id = sf.staff_id

-- 8
select
    f.title,
    CONCAT(a.first_name, ' ', a.last_name)
from film f
    join film_actor fa on f.film_id = fa.film_id
    join actor a on fa.actor_id = a.actor_id
order by
    f.title

-- 9
select
    CONCAT(a.first_name, ' ', a.last_name),
    f.title
from film f
    join film_actor fa on f.film_id = fa.film_id
    join actor a on fa.actor_id = a.actor_id
order by
    a.last_name, a.first_name

-- 10
select
    f.title
from
    film f
    join film_category fc on f.film_id = fc.film_id
    join category c on fc.category_id = c.category_id
where
    c.name = 'HORROR'

-- 11
select
    s.store_id,
    a_st.address as store_address,
    concat(sf.first_name, ' ', sf.last_name) as spravce,
    a_sf.address as staff_address
from
    store s
    join staff sf on s.manager_staff_id = sf.staff_id
    join address a_sf on sf.address_id = a_sf.address_id
    join address a_st on s.address_id = a_st.address_id

-- 12
select
    f.film_id,
    f.title,
    fa.actor_id,
    fc.category_id
from
    film f
    join film_category fc on f.film_id = fc.film_id
    join film_actor fa on f.film_id = fa.film_id
order by
    film_id,
    actor_id

-- 13
select
    distinct
    fa.actor_id,
    fc.category_id
from
    film f
    join film_category fc on f.film_id = fc.film_id
    join film_actor fa on f.film_id = fa.film_id
order by
    actor_id

-- 14
select
    distinct film.title
from
    film
    join inventory on film.film_id = inventory.film_id

-- 15
select
    distinct concat(a.first_name, ' ', a.last_name)
from
    film f
    join film_actor fa on f.film_id = fa.film_id
    join actor a on fa.actor_id = a.actor_id
    join film_category fc on f.film_id = fc.film_id
    join category c on fc.category_id = c.category_id
where
    c.name = 'Comedy'

-- 16
select
    distinct
    concat(cu.first_name, ' ', cu.last_name) as customer
from
    country co
    join city ci on co.country_id = ci.country_id
    join address adr on ci.city_id = adr.city_id
    join customer cu on adr.address_id = cu.address_id
    join rental re on cu.customer_id = re.customer_id
    join inventory inv on re.inventory_id = inv.inventory_id
    join film f on inv.film_id = f.film_id
where
    co.country = 'Italy' AND
    f.title = 'Motions details'


-- 17
select
    concat(c.first_name, ' ', c.last_name) as customer,
    f.title
from
    customer c
    join rental r on c.customer_id = r.customer_id
    join inventory i on r.inventory_id = i.inventory_id
    join film f on i.film_id = f.film_id
    join film_actor fa on f.film_id = fa.film_id
    join actor a on a.actor_id = fa.actor_id
where
    a.first_name = 'Sean' AND
    a.last_name = 'Guiness' AND
    r.return_date is null


-- 18
select
    payment.payment_id, payment.amount, payment.payment_date
from
    rental
    left join payment on rental.rental_id = payment.rental_id


-- 19
select
    f.title,
    l.name
from
    language l
    left join dbo.film f on l.language_id = f.language_id

-- 20
select
    film.title,
    l.name,
    ol.name
from
    film
    join language l on film.language_id = l.language_id
    left join language ol on film.original_language_id = l.language_id


-- 21
select
    distinct f.title
from
    film f
    left join dbo.inventory i on f.film_id = i.film_id
    left join dbo.rental r2 on i.inventory_id = r2.inventory_id
    left join dbo.customer c on c.customer_id = r2.customer_id
where
    c.first_name = 'Tim' AND
    c.last_name = 'Cary' OR
    f.length = 48

-- 22
select
    film.title
from
    film
    left join dbo.inventory i on film.film_id = i.film_id
where
    i.inventory_id is null

-- 23
select
    distinct
    c.first_name,
    c.last_name
from
    customer c
    join rental r on c.customer_id = r.customer_id
    left join payment p on r.rental_id = p.rental_id
where
    p.payment_id is null

-- 24
SELECT
    film.title, language.name
FROM
    film
    LEFT JOIN language ON film.language_id = language.language_id AND
    language.name LIKE 'I%'


-------------------------------------------
--        Third lecture
-------------------------------------------

-- 1
select
    f.rating,
    count(*) as pocat_kat
from
    film f
group by
    f.rating

-- 2
select
    customer_id,
    count(c.last_name)
from
    customer c
group by
    c.customer_id

-- 3
select
    c.customer_id,
    CONCAT(c.first_name, ' ', c.last_name) as customer,
    count(p.payment_id) as payments
from
    customer c
    join dbo.payment p on c.customer_id = p.customer_id
group by
    c.customer_id , c.first_name, c.last_name
order by
    count(p.payment_id)

-- 4
select
    a.first_name,
    a.last_name,
    count(*) as same
from
    actor a
group by
    a.first_name,
    a.last_name
order by
    same DESC

--  5
select
    year(payment_date) as year,
    month(payment_date) as month,
    sum(amount) as sum
from
    payment
group by
    year(payment_date),
    month(payment_date)
order by
    year,
    month

-- 6
select
    store_id, count(*)
from
    inventory
group by
    store_id
    having count(*) > 2300

-- 7
select
    f.language_id,
    min(f.length)
from
    film f
group by
    f.language_id
having
    min(f.length) > 46


-- 8
select
    year(payment_date),
    month(payment_date),
    sum(amount)
from
    payment p
group by
    year(payment_date),
    month(payment_date)
having
    sum(amount) > 20000

-- 9
-- idk hard

-- 11
select
    l.name,
    count(*) as film_count
from
    film f
    join dbo.language l on f.language_id = l.language_id
group by
    l.name

-- 12

SELECT
    language.language_id,
    language.name,
    COUNT(film.film_id) AS pocet_filmu
FROM
language
    LEFT JOIN film ON language.language_id = film.language_id
GROUP BY language.language_id, language.name
    -- Aggregation functions are usually left joined

-- 13
select
    c.customer_id,
    c.first_name,
    c.last_name,
    count(r.rental_id) as rental_count
from
    customer c
    left join rental r on c.customer_id = r.customer_id
group by
    c.customer_id, c.first_name, c.last_name


-- 14
select
    c.customer_id,
    c.first_name,
    c.last_name,
    count(distinct i.film_id) as no_rented
from
    customer c
    left join dbo.rental r on c.customer_id = r.customer_id
    left join dbo.inventory i on r.inventory_id = i.inventory_id
group by
    c.customer_id,
    c.first_name,
    c.last_name

-- 15
select
    a.actor_id,
    concat(a.first_name, ' ', a.last_name) as actor,
    count(*) as nof
from
    film
    join dbo.film_actor fa on film.film_id = fa.film_id
    join dbo.actor a on a.actor_id = fa.actor_id
group by
    a.actor_id,
    a.first_name,
    a.last_name
having
    count(fa.film_id) > 20

-- 16
select
    c.customer_id,
    MIN(p.amount) as min_rent,
    AVG(p.amount) as avg_rent,
    MAX(p.amount) as max_rent
from
    customer c
    left join dbo.payment p on c.customer_id = p.customer_id
    left join dbo.rental r2 on c.customer_id = r2.customer_id
group by
    c.customer_id
order by
    c.customer_id

-- 17
select
    c.name,
    avg(cast(f.length as float)) as film_len
from
    category c
    left join dbo.film_category fc on c.category_id = fc.category_id
    left join dbo.film f on f.film_id = fc.film_id
group by
    c.name
order by
    avg(f.length)

-- 18
select
    i.film_id,
    sum(p2.amount) as profit
from
    inventory i
    join dbo.rental r2 on i.inventory_id = r2.inventory_id
    join dbo.payment p2 on r2.rental_id = p2.rental_id
group by
    i.film_id
having
    sum(p2.amount) > 100

-- 19
select
    a.actor_id,
    count(distinct fc.category_id) as no_cat
from
    actor a
    left join dbo.film_actor fa on a.actor_id = fa.actor_id
    left join dbo.film_category fc on fa.film_id = fc.film_id
group by
    a.actor_id
order by
    no_cat asc

-- 23
select
    c.first_name, c.last_name, c2.city, c3.country,
    count(distinct fc.category_id) as no_cat
from
    customer c
    join dbo.address a on a.address_id = c.address_id
    join dbo.city c2 on c2.city_id = a.city_id
    join dbo.country c3 on c3.country_id = c2.country_id
    left join dbo.rental r2 on c.customer_id = r2.customer_id
    left join dbo.inventory i on r2.inventory_id = i.inventory_id
    left join dbo.film_category fc on i.film_id = fc.film_id
group by
    c.first_name, c.last_name, c2.city, c3.country
having
    c3.country = 'Poland'


---------------------------------------------------------------
-- 4th lecture
---------------------------------------------------------------
-- this or this
SELECT film_id, title FROM film
WHERE
    film_id IN (
        SELECT film_id FROM film_actor
        WHERE actor_id = 1 OR actor_id = 10
    )
    AND NOT
    (
        film_id IN (
        SELECT film_id FROM film_actor WHERE actor_id = 1 ) AND
        film_id IN (
        SELECT film_id FROM film_actor WHERE actor_id = 10 )
    )

-- 7
select f.title
from film f
where not exists(
          select *
          from actor a
          join dbo.film_actor fa on a.actor_id = fa.actor_id
          where fa.film_id = f.film_id AND
                a.first_name = 'Penelope' AND
                a.last_name = 'Guiness'
      )


-- 9
select c.first_name, c.last_name
from customer c
where exists(
        select *
        from rental r
        join dbo.inventory i on r.inventory_id = i.inventory_id
        join dbo.film f on i.film_id = f.film_id
        where f.title = 'Enemy odds' and
              c.customer_id = r.customer_id
      ) and exists(
        select *
        from rental r
        join dbo.inventory i on r.inventory_id = i.inventory_id
        join dbo.film f on i.film_id = f.film_id
        where f.title = 'pollock deliverance' and
              c.customer_id = r.customer_id
      ) and exists(
        select *
        from rental r
        join dbo.inventory i on r.inventory_id = i.inventory_id
        join dbo.film f on i.film_id = f.film_id
        where f.title = 'falcon volume' and
              c.customer_id = r.customer_id
      )



SELECT actor.first_name, actor.last_name
FROM actor
WHERE EXISTS (
    SELECT *
    FROM film
    JOIN film_actor ON film.film_id = film_actor.film_id
    WHERE film_actor.actor_id = actor.actor_id AND film.length < 50
)





---------------------------------------------------------------
-- TEST
---------------------------------------------------------------
-- ut 12:30 VARIANTA A
-- A
with tab as (
    select
       o.jmeno,
       o.prijmeni,
       org.id_organ,
       count(distinct zhp.id_hlasovani) as zmatecne
    from
        organ org
        join dbo.hlasovani h on org.id_organ = h.id_organ
        join dbo.zmatecne_hlasovani_poslanec zhp on h.id_hlasovani = zhp.id_hlasovani
        join dbo.osoba o on zhp.id_osoba = o.id_osoba
    group by
        o.jmeno, o.prijmeni, org.id_organ
)
select
    *
from tab t1
where zmatecne = (
        select max(zmatecne)
        from tab t2
        where t1.id_organ = t2.id_organ
        )


-- 2
select hl.id_hlasovani, hl.datum, hl.nazev_dlouhy,(
    select count(*)
    from hlasovani_poslanec hp
    join dbo.poslanec p on p.id_poslanec = hp.id_poslanec
    join dbo.osoba o on o.id_osoba = p.id_osoba
    join dbo.zarazeni z on o.id_osoba = z.id_osoba
    join dbo.organ o2 on z.id_of = o2.id_organ AND z.cl_funkce = 0
    -- 0 = organ
    -- 1 = function
    where hl.id_hlasovani = hp.id_hlasovani AND
          hp.vysledek = 'A' AND
          o2.zkratka = 'ODS' AND
          o2.rodic_id_organ = hl.id_organ
          -- timto spojuju dve obdobi
    ),(
    select count(*)
    from hlasovani_poslanec hp
    join dbo.poslanec p on p.id_poslanec = hp.id_poslanec
    join dbo.osoba o on o.id_osoba = p.id_osoba
    join dbo.zarazeni z on o.id_osoba = z.id_osoba
    join dbo.organ o2 on z.id_of = o2.id_organ AND z.cl_funkce = 0
    where hl.id_hlasovani = hp.id_hlasovani AND
          hp.vysledek = 'A' AND
          o2.zkratka = 'ANO' AND
          -- zkratka = strana
          o2.rodic_id_organ = hl.id_organ
          -- timto spojuju dve obdobi
    )
from hlasovani hl
where hl.datum = '2019-10-24' AND
      hl.cislo = 172


-- 3
select s.id_schuze, s.schuze, s.do_schuze
from schuze s
join dbo.hlasovani h2 on s.id_organ = h2.id_organ
where year(s.do_schuze) = 2015 AND s.id_schuze NOT IN(
        select z.id_hlasovani
        from hlasovani h
        join dbo.zmatecne z on h.id_hlasovani = z.id_hlasovani
    )

-- skupina B
select s.id_schuze, s.schuze, s.do_schuze
from schuze s
where exists(
          select 1
          from hlasovani hl
          where s.schuze = hl.schuze AND
                (year(s.od_schuze) = 2020 OR year(s.do_schuze) = 2020) and
                hl.id_organ = s.id_organ
      ) and not exists(
          select 1
          from hlasovani hl
          join dbo.zmatecne z on hl.id_hlasovani = z.id_hlasovani
          where s.schuze = hl.schuze AND
                hl.id_organ = s.id_organ
      )



-- utery, 14:00
SELECT t.zkratka, count(*)
FROM (
	SELECT org.zkratka, org.nazev_organu_cz, ps.od_organ, count(*) cnt
	FROM poslanec p
	JOIN zarazeni z ON p.id_osoba = z.id_osoba
	JOIN organ org ON z.id_of = org.id_organ
	JOIN typ_organu typo ON org.id_typ_org = typo.id_typ_org
	JOIN organ ps ON ps.id_organ = p.id_organ and org.rodic_id_organ = ps.id_organ
	WHERE typo.nazev_typ_org_cz = 'klub'
	GROUP BY org.zkratka, ps.od_organ, org.nazev_organu_cz
	HAVING count(*) >= 50
) t
GROUP BY t.zkratka
HAVING count(*) >= 2
----------------------------------------->>>> toto si projit zitra znova

-- 2
with tab as (
    select hl.id_hlasovani, hl.schuze, hl.cislo, hl.nazev_dlouhy
    from schuze s
    join hlasovani hl on s.id_organ = hl.id_organ AND s.schuze = hl.schuze
    join dbo.organ o on hl.id_organ = o.id_organ
    where year(o.od_organ) = 2013 AND year(o.do_organ) = 2017
)

select *
from tab t1
where t1.cislo = (
        select max(t2.cislo)
        from tab t2
        where t1.schuze = t2.schuze
    )


-- 3
select id_osoba
from osoba o
where exists(
        select *
        from poslanec p
        join hlasovani_poslanec hp on p.id_poslanec = hp.id_poslanec
        join hlasovani h on hp.id_hlasovani = h.id_hlasovani
        join dbo.organ org on h.id_organ = org.id_organ
        where h.nazev_dlouhy like 'Návrh na vyslovení nedůvěry vládě%' AND
              year(org.od_organ) = 2017 AND
              p.id_osoba = o.id_osoba
) and not exists(
        select *
        from poslanec p
        join hlasovani_poslanec hp on p.id_poslanec = hp.id_poslanec
        join hlasovani h on hp.id_hlasovani = h.id_hlasovani
        join dbo.organ og on h.id_organ = og.id_organ
        where h.nazev_dlouhy like 'Návrh na vyslovení nedůvěry vládě%' AND
              year(og.od_organ) = 2017 AND
              hp.vysledek = 'A' AND
              p.id_osoba = o.id_osoba
)
order by o.id_osoba

select *
from osoba and exists (
	select 1
	from hlasovani
	join hlasovani_poslanec hp on hlasovani.id_hlasovani = hp.id_hlasovani
	join poslanec on poslanec.id_poslanec = hp.id_poslanec
	join organ on hlasovani.id_organ = organ.id_organ
	where nazev_dlouhy LIKE 'NĂˇvrh na vyslovenĂ­ nedĹŻvÄ›ry vlĂˇdÄ›%' and
		 year(organ.od_organ) = 2017 and
		 poslanec.id_osoba = osoba.id_osoba
)
order by id_osoba















with tab as (
    select hl.id_hlasovani, hl.schuze, hl.cislo, hl.nazev_dlouhy
    from hlasovani hl
    order by hl.schuze
)
select *
from tab t1
where



with tab as (
	select id_hlasovani, schuze.schuze, cislo, nazev_dlouhy
	from schuze
	join hlasovani on schuze.schuze = hlasovani.schuze
	join organ on organ.id_organ = schuze.id_organ
	where year(organ.od_organ) = 2013 and
						schuze.id_organ = hlasovani.id_organ
)
select *
from tab t1
where t1.cislo = (
  select MAX(cislo)
  from tab t2
  where t1.schuze = t2.schuze
)
order by t1.schuze

-- 3
select *
from osoba
where not exists (
    select 1
    from poslanec p
    join dbo.hlasovani_poslanec hp on p.id_poslanec = hp.id_poslanec
    join dbo.hlasovani h on hp.id_hlasovani = h.id_hlasovani
    join dbo.organ o on h.id_organ = o.id_organ
    where h.nazev_dlouhy like 'Návrh na vyslovení nedůvěry vládě%' AND
          year(o.od_organ) between 2017 and 2021 AND
          hp.vysledek in ('A') AND
          p.id_osoba = osoba.id_osoba
) and exists (
    select 1
    from poslanec p
    join dbo.hlasovani_poslanec hp on p.id_poslanec = hp.id_poslanec
    join dbo.hlasovani h on hp.id_hlasovani = h.id_hlasovani
    join dbo.organ o on h.id_organ = o.id_organ
    where h.nazev_dlouhy like 'Návrh na vyslovení nedůvěry vládě%' AND
          year(o.od_organ) between 2017 and 2021 AND
          hp.vysledek not in ('A') AND
          p.id_osoba = osoba.id_osoba
)
order by id_osoba


-- Streda 10:45 ----------------------------------------
--A/2
with tab as (
    select distinct o.id_osoba, o.prijmeni, o.jmeno,(
        select count(o2.id_poslanec)
        from poslanec p
        join dbo.omluva o2 on p.id_poslanec = o2.id_poslanec
        where p.id_osoba = o.id_osoba and
        month(o2.den) = 11
        having count(o2.id_poslanec) > 16
    ) as listopad ,(
        select count(o2.id_poslanec)
        from poslanec p
        join dbo.omluva o2 on p.id_poslanec = o2.id_poslanec
        where p.id_osoba = o.id_osoba and
        month(o2.den) = 12
    ) as prosinec
    from osoba o
    join dbo.zarazeni z on o.id_osoba = z.id_osoba and cl_funkce = 0
    join dbo.organ org on z.id_of = org.id_organ
    where org.nazev_organu_cz = 'Poslanecký klub Občanské demokratické strany'
)

select *
from tab t1
where listopad > prosinec

-- 3
with tab as (
    select o.id_osoba, o.jmeno, o.prijmeni, org.nazev_organu_cz, count(*) as pocet_klubu
    from osoba o
    join zarazeni z on o.id_osoba = z.id_osoba
    join organ org on z.id_of = org.id_organ and z.cl_funkce = 0
    where org.nazev_organu_cz like '%klub%'
    group by o.id_osoba, o.jmeno, o.prijmeni, org.nazev_organu_cz
    having count(*) > 6
)

select *
from tab t1;

with tab as (
    select o.id_osoba, o.jmeno, o.prijmeni, org.nazev_organu_cz
    from osoba o
    join zarazeni z on o.id_osoba = z.id_osoba
    join organ org on z.id_of = org.id_organ and z.cl_funkce = 0
    where org.nazev_organu_cz like '%klub%'
)

select *
from tab t1



-- 2

select o1.id_osoba, o1.jmeno, o1.prijmeni, (
        select count(*)
        from osoba os
        join dbo.poslanec p on os.id_osoba = p.id_osoba
        join dbo.omluva o on p.id_poslanec = o.id_poslanec and p.id_organ = o.id_organ
        where month(o.den) < 7 AND
              year(o.den) = 2021 AND
              o1.id_osoba = os.id_osoba
        having count(*) > 47
        group by os.id_osoba, os.jmeno, os.prijmeni
    ) as oml_1_6, (
        select count(*)
        from osoba os
        join dbo.poslanec p on os.id_osoba = p.id_osoba
        join dbo.omluva o on p.id_poslanec = o.id_poslanec and p.id_organ = o.id_organ
        where month(o.den) > 6 AND
            year(o.den) = 2021 AND
            o1.id_osoba = os.id_osoba
        group by os.id_osoba, os.jmeno, os.prijmeni
    ) as oml_7_12
from osoba o1



WITH OmluvaCounts AS (
    SELECT p.id_osoba,
           SUM(CASE WHEN month(o.den) BETWEEN 1 AND 6 AND year(o.den) = 2021 THEN 1 ELSE 0 END) as oml_1_6,
           SUM(CASE WHEN month(o.den) BETWEEN 7 AND 12 AND year(o.den) = 2021 THEN 1 ELSE 0 END) as oml_7_12
    FROM poslanec p
    JOIN dbo.omluva o ON p.id_poslanec = o.id_poslanec
    GROUP BY p.id_osoba
)
SELECT o1.id_osoba, o1.jmeno, o1.prijmeni, oc.oml_1_6, oc.oml_7_12
FROM osoba o1
JOIN OmluvaCounts oc ON o1.id_osoba = oc.id_osoba





-- 1
select o.id_osoba, o.jmeno, o.prijmeni, z.od_o, z.do_o
from osoba o
join zarazeni z on o.id_osoba = z.id_osoba and z.cl_funkce = 0
where exists(
            select *
            from organ org
            where org.nazev_organu_cz like 'Poslanecký klub Unie svobody' AND
                  z.id_of = org.id_organ
      ) and not exists(
            select *
            from organ org
            where org.nazev_organu_cz like 'Poslanecký klub Občanské demokratické strany' AND
                  z.id_of = org.id_organ
      )


WITH OmluvaCounts AS (
    SELECT p.id_osoba,
           SUM(CASE WHEN month(o.den) BETWEEN 1 AND 6 AND year(o.den) = 2021 THEN 1 ELSE 0 END) as oml_1_6,
           SUM(CASE WHEN month(o.den) BETWEEN 7 AND 12 AND year(o.den) = 2021 THEN 1 ELSE 0 END) as oml_7_12
    FROM poslanec p
    JOIN dbo.omluva o ON p.id_poslanec = o.id_poslanec
    GROUP BY p.id_osoba
)
SELECT o1.id_osoba, o1.jmeno, o1.prijmeni, oc.oml_1_6, oc.oml_7_12
FROM osoba o1
JOIN OmluvaCounts oc ON o1.id_osoba = oc.id_osoba

select o.id_osoba, o.prijmeni, t.nazev_typ_org_cz, count(*) as pocet_klubu
from osoba o
join dbo.zarazeni z on o.id_osoba = z.id_osoba
join organ org on z.id_of = org.id_organ and z.cl_funkce = 0
join dbo.typ_organu t on org.id_typ_org = t.id_typ_org
where t.nazev_typ_org_cz = 'klub' AND
      org.do_organ is null
group by o.id_osoba, o.prijmeni, t.nazev_typ_org_cz
having count(*) > 1


select o.id_osoba, o.jmeno, o.prijmeni,
  count(distinct org.nazev_organu_cz) as pocet_ruznych_klubu,
  sum(datediff(month, z.od_o, do_o)) pocet_mesicu_ukoncenych_clenstvi
from osoba o
join zarazeni z on o.id_osoba=z.id_osoba
join organ org on z.id_of=org.id_organ and z.cl_funkce=0
join typ_organu tor on tor.id_typ_org=org.id_typ_org
join poslanec p on p.id_osoba=o.id_osoba
join organ snemovna on p.id_organ=snemovna.id_organ
where tor.nazev_typ_org_cz='Klub' and year(snemovna.od_organ)=2021 and
      org.od_organ >= snemovna.od_organ
group by o.id_osoba, o.jmeno, o.prijmeni
having count(distinct org.nazev_organu_cz) > 1
order by pocet_ruznych_klubu desc












-- Vyberte vsechny osoby, ktere se narodily po roce 1990 a pro ne pocty kolikrat byli predsedy a v kolika byli klubec
select o.id_osoba, o.jmeno, o.prijmeni, (
        select count(*)
        from osoba op
        join zarazeni z on op.id_osoba = z.id_osoba
        join funkce f on z.id_of = f.id_funkce AND z.cl_funkce = 1
        where o.id_osoba = op.id_osoba AND
              f.nazev_funkce_cz like '%předseda%'
    ) as pocet_predseda, (
        select count(*)
        from osoba ok
        join zarazeni z on ok.id_osoba = z.id_osoba
        join organ org on z.id_of = org.id_organ AND z.cl_funkce = 0
        where ok.id_osoba = o.id_osoba AND
              org.nazev_organu_cz like '%klub%'
    ) as pocet_klub
from osoba o
where year(o.narozeni) > 1990


select organ.nazev_organu_cz
from organ


-- Vyberte vsechny osoby, ktere byly ve strane ANO a nikdy nemeli funcki ministra tak nejak bylo to zadani
select o.id_osoba, o.jmeno, o.prijmeni
from osoba o
where exists(
    select *
    from osoba o1
    join zarazeni z on o1.id_osoba = z.id_osoba
    join organ org on z.id_of = org.id_organ AND z.cl_funkce = 0
    where o1.id_osoba = o.id_osoba AND
          org.zkratka = 'ANO'
) and not exists(
    select *
    from osoba op
    join zarazeni z on op.id_osoba = z.id_osoba
    join funkce f on z.id_of = f.id_funkce AND z.cl_funkce = 1
    where o.id_osoba = op.id_osoba AND
          f.nazev_funkce_cz like '%ministr%'
)
order by o.id_osoba




















select o.id_osoba, o.jmeno, o.prijmeni
from osoba o
join zarazeni z on o.id_osoba = z.id_osoba
join organ org on z.id_of = org.id_organ and z.cl_funkce = 0