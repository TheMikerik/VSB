--CV3

-- 1
SELECT *
FROM city
JOIN country ON city.country_id = country.country_id

-- 5
SELECT customer.first_name, customer.last_name, address.address, city.city
FROM
	customer
	JOIN address ON customer.address_id = address.address_id
	JOIN city ON address.city_id = city.city_id

-- 6
SELECT customer.first_name, customer.last_name, city.city
FROM
	customer
	JOIN address ON customer.address_id = address.address_id
	JOIN city ON address.city_id = city.city_id

-- 8
SELECT film.title, actor.first_name, actor.last_name
FROM
	film
	JOIN film_actor ON film.film_id = film_actor.film_id
	JOIN actor ON film_actor.actor_id = actor.actor_id
ORDER BY film.title

-- 9
SELECT film.title, actor.first_name, actor.last_name
FROM
	film
	JOIN film_actor ON film.film_id = film_actor.film_id
	JOIN actor ON film_actor.actor_id = actor.actor_id
ORDER BY actor.first_name, actor.last_name

-- 10
SELECT film.title, category.name
FROM
	film
	JOIN film_category ON film.film_id = film_category.film_id
	JOIN category ON film_category.category_id = category.category_id
	WHERE category.name = 'Horror'

-- 11
SELECT
	store.store_id, staff.first_name, staff.last_name,
	ad_staff.address AS staff_address,
	ad_store.address AS store_address
FROM
	store
	JOIN staff ON store.store_id = staff.store_id
	JOIN address ad_staff ON staff.address_id = ad_staff.address_id
	JOIN address ad_store ON store.address_id = ad_store.address_id

-- 12
SELECT
	film.film_id, film.title,
	act.actor_id, cat.category_id
FROM
	film
	JOIN film_actor act ON film.film_id = act.film_id
	JOIN film_category cat ON film.film_id = cat.film_id
ORDER BY film.film_id


-- 13
SELECT
	DISTINCT act.actor_id, cat.category_id
FROM
	film
	JOIN film_actor act ON film.film_id = act.film_id
	JOIN film_category cat ON film.film_id = cat.film_id
ORDER BY act.actor_id, cat.category_id


-- 14
SELECT
	DISTINCT film.title
FROM
	rental
	JOIN inventory inv ON rental.inventory_id = inv.inventory_id
	JOIN film ON inv.film_id = film.film_id





----------------------------------------- LEFT JOIN
-- 19
SELECT
	*
FROM
	language
	LEFT JOIN film ON language.language_id = film.language_id


-- 20
SELECT
	film.title,
	lan.name AS language,
	orlan.name AS original_langage
FROM
	film
	JOIN language lan ON film.language_id = lan.language_id
	LEFT JOIN language orlan ON film.original_language_id = orlan.language_id