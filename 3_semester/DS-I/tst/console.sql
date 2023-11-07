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