-- 1
SELECT
	film_id, title,
	(
		SELECT COUNT(*)
		FROM film_actor
		WHERE film_actor.film_id = film.film_id
	) AS pocet_hercu,
	(
		SELECT COUNT(*)
		FROM film_category
		WHERE film_category.film_id = film.film_id
	) AS pocet_kategorii
FROM film
	
-- 6
SELECT customer.customer_id, customer.first_name, customer.last_name
FROM customer
WHERE
	(
		SELECT COUNT(*)
		FROM payment
		WHERE payment.customer_id = customer.customer_id AND amount > 4
	) >
	(
		SELECT COUNT(*)
		FROM payment
		WHERE payment.customer_id = customer.customer_id AND amount <= 4
	)

-- 7
SELECT actor.first_name, actor.last_name
FROM actor
WHERE(
	SELECT COUNT(*)
	FROM film_actor
	WHERE film_actor.actor_id = actor.actor_id AND film_id IN (
		SELECT film_id
		FROM film_category
			JOIN category ON film_category.category_id = category.category_id
		WHERE category.name = 'comedy'
		)
	)
	>
	(
		SELECT COUNT(*)
			FROM film_actor
			WHERE film_actor.actor_id = actor.actor_id AND film_id IN (
				SELECT film_id
				FROM film_category
				JOIN category ON film_category.category_id = category.category_id
			WHERE category.name = 'horror'
		)
) * 2

-- 13
SELECT f.title
FROM film f
WHERE f.length = (SELECT MAX(length) FROM film)

-- 14
SELECT rating, film_id, title, length
FROM film f
WHERE f.length = (SELECT MAX(f2.length) FROM film f2 WHERE f.rating = f2.rating)

-- 16
WITH T AS
(
	SELECT actor.actor_id, actor.first_name, actor.last_name, film.film_id, film.title, film.length
	FROM
		actor
		JOIN film_actor ON actor.actor_id = film_actor.actor_id
		JOIN film ON film_actor.film_id = film.film_id
)SELECT *
FROM T t1
WHERE t1.length = (SELECT MAX(t2.length) FROM T t2 WHERE t1.actor_id = t2.actor_id)
-- 19

SELECT *
FROM customer
WHERE
	customer_ID IN (
		SELECT rental.customer_id
		FROM
			rental
			JOIN inventory ON rental.inventory_id = inventory.inventory_id
			JOIN film ON inventory.film_id = film.film_id
		WHERE
			film.length = (SELECT MAX(length) FROM film)
	)
	AND customer_id IN (
		SELECT rental.customer_id
		FROM
			rental
			JOIN inventory ON rental.inventory_id = inventory.inventory_id
			JOIN film ON inventory.film_id = film.film_id
		WHERE
			film.length = (SELECT MIN(length) FROM film)
	)


-- 22
