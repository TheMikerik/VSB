
nonZeros (x:xs) = tmp (x:xs) [] where
    tmp [] ys = ys
    tmp (x:xs) ys | x == 0 = tmp xs ys
                  | otherwise = tmp xs (x:ys)