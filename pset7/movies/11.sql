SELECT movies.title
FROM ((movies INNER JOIN ratings ON movies.id = ratings.movie_id) INNER JOIN stars ON stars.movie_id = movies.id)
WHERE stars.person_id = (SELECT id FROM people WHERE name = "Chadwick Boseman")
ORDER BY ratings.rating DESC LIMIT 5

-- SELECT movies.title, movies.id, ratings.rating
-- FROM movies
-- INNER JOIN ratings ON movies.id = ratings.movie_id AND movies.title in
-- (
-- SELECT title FROM movies WHERE id in
-- 	(
-- 		SELECT movie_id FROM ratings WHERE movie_id in
-- 			(SELECT movie_id FROM stars WHERE person_id =
-- 				(SELECT id FROM people WHERE name = "Chadwick Boseman")
-- 			)
-- 		ORDER BY ratings.rating DESC LIMIT 5
-- 	)
-- )
-- ORDER BY ratings.rating DESC