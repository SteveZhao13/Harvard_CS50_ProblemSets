SELECT title FROM movies WHERE id in
(
	SELECT movie_id FROM
	(
	SELECT movie_id FROM stars WHERE person_id in
		(SELECT id FROM people WHERE name = "Johnny Depp")
	)
	WHERE movie_id in
	(
	SELECT movie_id FROM stars WHERE person_id in
		(SELECT id FROM people WHERE name = "Helena Bonham Carter")
	)
)


-- SELECT title FROM movies WHERE id in
-- (
-- 	SELECT m2.movie_id
-- 	FROM
-- 	(
-- 	SELECT movie_id FROM stars WHERE person_id in
-- 		(SELECT id FROM people WHERE name = "Johnny Depp")
-- 	) m1
-- 	INNER JOIN
-- 	(
-- 	SELECT movie_id FROM stars WHERE person_id in
-- 		(SELECT id FROM people WHERE name = "Helena Bonham Carter")
-- 	) m2
-- 	ON m1.movie_id = m2.movie_id
-- )


-- SELECT title FROM movies WHERE id in
-- (
-- 	SELECT movie_id FROM
-- 	(
-- 		SELECT movie_id FROM stars WHERE person_id in
-- 			(SELECT id FROM people WHERE name = "Johnny Depp")
-- 		UNION ALL
-- 		SELECT movie_id FROM stars WHERE person_id in
-- 			(SELECT id FROM people WHERE name = "Helena Bonham Carter")
-- 	)
-- 	GROUP BY movie_id
-- 	HAVING count(*) > 1
-- )


-- SELECT title FROM movies WHERE id in
-- (
-- 	SELECT id FROM movies WHERE id in
-- 		(SELECT movie_id FROM stars WHERE person_id in
-- 			(SELECT id FROM people WHERE name = "Johnny Depp"))
-- 		AND id in
-- 		(SELECT movie_id FROM stars WHERE person_id in
-- 			(SELECT id FROM people WHERE name = "Helena Bonham Carter"))
-- )