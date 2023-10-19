-- 1
SELECT rating, COUNT(*) AS pocet
FROM film
GROUP BY rating

-- 5
SELECT MONTH(payment_date) AS Mesic, YEAR(payment_date) AS Rok, SUM(amount) AS Castka
FROM payment
group by MONTH(payment_date), YEAR(payment_date)

-- 6
SELECT store_id, COUNT (*) AS pocet
FROM inventory
GROUP BY store_id
HAVING COUNT(*) > 2300

-- 10
SELECT language_id, COUNT(film_id) as ID 
FROM film
GROUP BY language_id

-- 11
SELECT lan.name, COUNT(film_id) as ID 
FROM film
JOIN language lan ON film.language_id = lan.language_id
GROUP BY lan.name

-- 12
SELECT lan.language_id, lan.name, COUNT(film.film_id) as ID 
FROM language lan
LEFT JOIN film ON film.language_id = lan.language_id
GROUP BY lan.language_id, lan.name

-- 13
SELECT customer.customer_id, customer.first_name, customer.last_name, COUNT(rental_id) as suma
FROM customer
LEFT JOIN rental on customer.customer_id = rental.customer_id
GROUP BY customer.customer_id, customer.first_name, customer.last_name
HAVING COUNT(rental_id) > 30

-- 16
SELECT c.customer_id, c.first_name, c.last_name, COALESCE(SUM(p.amount), 0) as suma, MIN(p.amount) as minimum, MAX(p.amount) as maximum, AVG(p.amount) as average 
FROM customer c
left join rental r on c.customer_id = r.customer_id
left join payment p on r.rental_id = p.rental_id
GROUP BY c.customer_id, c.first_name, c.last_name
ORDER BY suma DESC

-- 23
SELECT l.name, count(f.film_id) as pocet
FROM
	language l
	left join film f on
		l.language_id = f.language_id AND
		f.length > 350
group by l.language_id, l.name


-- 24
select  c.customer_id, c.first_name, c.last_name, COALESCE(SUM(p.amount), 0) as suma
from customer c
	left join rental r on c.customer_id = r.customer_id AND
		MONTH(rental_date) >= 6
	left join payment p on r.rental_id = p.rental_id
group by c.customer_id, c.first_name, c.last_name
