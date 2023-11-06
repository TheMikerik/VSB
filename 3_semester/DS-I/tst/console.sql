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

