--Možností, jak kódovat text, je nahradit časté dvojice znaků novými 
--(do té doby nepoužívanými) znaky. V tomto úkolu byste měli implementovat funkci,
--která dekóduje takový kódovaný text. Funkce decode přebírá kódovaný text a slovník.
--Slovník je posloupnost párů, kde první prvek je zakódovaný znak (Char) a druhý prvek
--je původní pár (jako String délky 2). Výsledkem je originální text. Což je ve
--skutečnosti text z parametru, kde byly všechny kódované znaky nahrazeny původními
--dvojicemi znaků.

--decode :: String -> [(Char,String)] -> String
--Main> decode "HAHA" [('E',"AB"),('F',"CD"),('G',"EF"),('H',"GG")]
--"ABCDABCDAABCDABCDA"

-- Solution :
decode :: String -> [(Char,String)] -> String
decode [] _ = []
decode (x:xs) to = case lookup x to of
                         Just new -> decode (new ++ xs) to
                         Nothing -> x : decode xs to

-- Old codes :

-- decodeForChars :: String -> Char -> Char -> String
-- decodeForChars [] o n = []
-- decodeForChars (x:xs) o n | x == o = n: decodeForChars xs o n
--                           | otherwise = x: decodeForChars xs o n 


-- decode1 :: String -> [(Char,String)] -> String
-- decode1 [] _ = []
-- decode1 (x:xs) [from,(to:tos)] | x == from = (to:tos): decode1 xs [from,(to:tos)]
--                                | otherwise = x: decode1 xs [from,(to:tos)]
 

-- decode2 :: String -> [(Char,String)] -> String
-- decode2 [] _ = []
-- decode2 (x:xs) [(from,(to:tos))]
--     | x == from = subs where subs = (x:xs)++(to:tos)
--     | otherwise = x: decode2 xs [(from,(to:tos))]


-- decode3 :: String -> [(Char,String)] -> String
-- decode3 [] _ = []
-- decode3 (x:xs) [(from,to)] = lookup x [(from,to)]
--     x == from = (to) ++ decode3 xs [(from,to)]
--     x /= from = [x] ++ decode3 xs [(from,to)]


-- decode4 :: String -> [(Char,String)] -> String
-- decode4 [] _ = []
-- decode4 (x:xs) [(from,to)] = lookup x [(from,to)]
--     if x == from
--     then (to) ++ decode4 xs [(from,to)]
--     else [x] ++ decode4 xs [(from,to)]


-- decode5 :: String -> [(Char,String)] -> String
-- decode5 [] _ = []
-- decode5 (x:xs) vzorek = case lookup x vzorek of
--                         Just nahrazeno -> decode5 (nahrazeno ++ xs) vzorek
--                         Nothing -> x : decode5 xs vzorek


-- decode6 :: String -> [(Char,String)] -> String
-- decode6 [] _ = []
-- decode6 (x:xs) to = case lookup x to of
--                         Just new -> decode6 (new ++ xs) to
--                         Nothing -> x : decode6 xs to