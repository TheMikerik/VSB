factorial  :: Int -> Int
factorial  0 = 1
factorial  n = n * factorial  (n-1)

combinations :: Int -> Int -> Int
combinations n k = (factorial n)