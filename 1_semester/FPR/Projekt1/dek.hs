--decode :: String -> [(Char,String)] -> String
--decode [] _ = []
--decode (x:xs) vzor = case lookup x vzor of
--                        Nothing -> x : decode xs vzor
--                        Just ys -> decode (ys ++ xs) vzor

-- decode1 :: String -> [(Char,String)] -> String
-- decode1 [] _ = []
-- decode1 (x:xs) vzor
--         | lookup x vzor = x == vzor : decode1 xs vzor
--         | otherwise decode1 (ys ++ xs) vzor

-- decode2 :: String -> [(Char,String)] -> String
-- decode2 [] [(from,(to:tos))] = []
-- decode2 (x:xs) [(from,(to:tos))]
--     | x == from = (to:tos): decode2 xs [(from,(to:tos))]
--     | otherwise = x: decode2 xs [(from,(to:tos))]

--decode2 :: String -> [(Char,String)] -> String
--decode2 [] _ = []
--decode2 (x:xs) [(from,tos)]
--    | x == from = connectPrev (tos) where
--        connectPrev [] (tos) = decode2 (tos) (tos)
--        connectPrev [y] (tos) = deocde2 (y)++(tos) (tos)
--        connectPrev (y:ys) (tos) = deocde2 (y:ys)++(tos) (tos)

-- decode3 :: String -> [(Char,String)] -> String
-- decode3 [] _ = []
-- decode3 (x:xs) [(from,to)]
--    | x == from = (to) ++ decode3 xs [(from,to)]
--    | otherwise = [x] ++ decode3 xs [(from,to)]

-- decode4 :: String -> [(Char,String)] -> String
-- decode4 [] _ = []
-- decode4 (x:xs) [(from,to)] = lookup x [(from,to)]
--     if x == from
--     then (to) ++ decode4 xs [(from,to)]
--     else [x] ++ decode4 xs [(from,to)]