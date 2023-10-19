-- 1 -------------------------------------------------
Select film.film_id, title
from film
	join film_actor ON film.film_id = film_actor.film_id
where film_actor.actor_id = 1

	-- IN --
select film_id, title
from film
where film_id in (
	select film_id
	from film_actor
	where actor_id = 1
)

	-- EXISTS -- 
select film_id, title
from film
where exists (
	select * 
	from film_actor
	where actor_id = 1 and film.film_id = film_actor.film_id
)


-- 2 -------------------------------------------------
select film_id
from film_actor
where actor_id = 1

-- 3 -------------------------------------------------
select film_id, title
from 
	film
where
	exists (
		select * 
		from film_actor
		where actor_id = 1 and film.film_id = film_actor.film_id
		) AND
	exists (
		select * 
			from film_actor
			where actor_id = 10 and film.film_id = film_actor.film_id
	)


	-- IN --
select film_id, title
from 
	film
where 
	film_id in (
		select film_id
		from film_actor
		where actor_id = 1
	) AND
	film_id in (
		select film_id
		from film_actor
		where actor_id = 10
	)


-- 4 -------------------------------------------------
select film_id, title
from 
	film
where 
	film_id in (
		select film_id
		from film_actor
		where actor_id = 1 or actor_id = 10
	)

-- 5 -------------------------------------------------
select film_id, title
from 
	film
where 
	film_id not in (
		select film_id
		from film_actor
		where actor_id = 1
	)
-- 6 -------------------------------------------------
select film_id, title
from 
	film
where 
	film_id in (
		select film_id
		from film_actor
		where actor_id = 1
	) or
	film_id in (
		select film_id
		from film_actor
		where actor_id = 10
	) and
	film_id not in (
		select film_id
		from film_actor
		where actor_id = 1 or actor_id = 10
	)

-- 7 --------------------------------------------------
select film_id, title
from 
	film
where 
	film_id in (
		select film_id
		from film_actor
		join actor on film_actor.actor_id = actor.actor_id
		where first_name = 'PENELOPE' and last_name = 'GUINESS'
	) AND
	film_id in (
		select film_id
		from film_actor
		join actor on film_actor.actor_id = actor.actor_id
		where first_name = 'CHRISTIAN' and last_name = 'GABLE'
	)
-- 12 -------------------------------------------------
SELECT title
FROM film f1
WHERE EXISTS
(
	SELECT *
	FROM film f2
	WHERE f1.length = f2.length AND f1.film_id != f2.film_id
)

-- 19 -------------------------------------------------
SELECT title
FROM film f1
WHERE
	NOT EXISTS (
		SELECT *
			FROM
				film f2
				JOIN film_actor ON f2.film_id = film_actor.film_id
				JOIN actor ON film_actor.actor_id = actor.actor_id
			WHERE
				actor.first_name = 'BURT' AND actor.last_name = 'POSEY' AND f2.length <= f1.length
)
-- 15 -------------------------------------------------
SELECT DISTINCT f1.title
FROM rental re
	JOIN inventory inv ON re.inventory_id = inv.inventory_id
	JOIN film f1 ON inv.film_id = f1.film_id
WHERE
	EXISTS (
		SELECT * 
		FROM
			rental r2
			JOIN inventory inv2 ON r2.inventory_id = inv2.inventory_id
		WHERE
			re.rental_id != r2.rental_id AND inv.film_id = inv2.film_id
)

-- 16 -------------------------------------------------
SELECT DISTINCT f1.title
FROM rental re
	JOIN inventory inv ON re.inventory_id = inv.inventory_id
	JOIN film f1 ON inv.film_id = f1.film_id
WHERE
	EXISTS (
		SELECT * 
		FROM
			rental r2
			JOIN inventory inv2 ON r2.inventory_id = inv2.inventory_id
		WHERE
			re.rental_id != r2.rental_id AND inv.film_id = inv2.film_id
)

-- 20 -------------------------------------------------
SELECT a.first_name, a.last_name
FROM film f
	JOIN film_actor fa ON f.film_id = fa.film_id
	JOIN actor a ON fa.actor_id = a.actor_id
WHERE
	NOT EXISTS (
		SELECT *
		FROM film
		WHERE film.length >= 180
) AND
WHERE fa.film_actor

SELECT actor.first_name, actor.last_name
FROM actor
WHERE
	NOT EXISTS (
		SELECT *
		FROM film
		JOIN film_actor ON film.film_id = film_actor.film_id
		WHERE film_actor.actor_id = actor.actor_id AND film.length >= 180
	) AND	actor_id IN (SELECT actor_id FROM film_actor)