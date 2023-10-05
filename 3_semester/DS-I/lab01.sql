-- CV1

-- 1
SELECT email
FROM customer
WHERE active = 0;

-- 2
SELECT title, description
FROM film
WHERE rating = 'G'
ORDER BY title DESC;

-- 3
SELECT *
FROM payment
WHERE YEAR(payment_date) >= 2006 AND amount < 2;

-- 4
SELECT rating, title, rental_duration
FROM film
WHERE rating = 'G' OR rating = 'PG'
ORDER BY title DESC;


-- 5
SELECT rating, title, description
FROM film
WHERE rating IN ('G', 'PG', 'PG-13')
ORDER BY rating ASC;

-- 6
SELECT rating, title, description
FROM film
WHERE rating NOT IN ('G', 'PG', 'PG-13')
ORDER BY rating DESC;

-- 7
SELECT *
FROM film
WHERE length > 50 AND (rental_duration = 3 OR rental_duration = 5)
ORDER BY rental_duration ASC;

-- 8
SELECT *
FROM film
WHERE (title LIKE '%RAINBOW%' OR title LIKE 'TEXAS%') AND length > 70;
			-- Like -> textove retezce
			-- % -> libovolny pocet libovolnych znaku

-- 9
SELECT title
FROM film
WHERE 
	description LIKE '%And%' AND
	length BETWEEN 80 AND 90 AND
	(rental_duration % 2 != 0);

-- 10
SELECT DISTINCT special_features
FROM film
WHERE replacement_cost BETWEEN 14 AND 16
ORDER BY special_features;


-- 12
SELECT *
FROM address
WHERE postal_code IS NULL;

-- 21
SELECT COUNT(*) - COUNT(*) + 69 AS pocet
FROM film;

-- 22
SELECT COUNT(DISTINCT rating) AS pocet
FROM film;

-- 23
SELECT COUNT(address) AS adresy, COUNT(postal_code) AS psc, COUNT(DISTINCT postal_code) AS psc2
FROM address;