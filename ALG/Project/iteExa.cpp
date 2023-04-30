1 Graph G(”MyGraph.txt”); // vytvoreni grafu
2 GraphIterator Iter (G); // vytvoreni iteratoru pro graf G
for(
Iter .Reset () ; // inicializace , reset , iteratoru
! Iter .IsEnd () ; // dotaz na konec pruchodu
Iter .Next() // posun na dalsi vrchol
)
{
cout << Iter .CurrentKey() ; // zpracovani vrcholu
}