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