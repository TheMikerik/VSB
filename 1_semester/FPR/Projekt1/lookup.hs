import GHC.Exts.Heap (GenClosure(value))
data Tree a = Leaf a | Branch a (Tree a) (Tree a)

myTree :: Tree Int
myTree = Branch 8 (Leaf 4) (Branch 9 (Leaf 40) (Leaf 5))

countTree :: Tree a -> Int
countTree (Leaf _) = 1
countTree (Branch _ x y) = 1 + countTree x + countTree y

maxTree :: Ord a => Tree a -> a
maxTree (Leaf x) = x
maxTree (Branch value x y) = max value (max (maxTree x) (maxTree y))

maxTree2 :: Ord a => Tree a -> a
maxTree2 tree = maximum (toList tree)

greaterThen :: Ord a => Tree a -> a -> Int
greaterThen (Leaf x) a
                    | x > a = 1
                    | otherwise = 0
greaterThen (Branch val x y) a
                        | val > a = 1 + greaterThen x a + greaterThen y a
                        | otherwise = greaterThen x a + greaterThen y a