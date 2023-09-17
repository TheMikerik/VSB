#include <stdio.h>

void vypis(); // Na začátku s můžu vypsat definice všech fcí
void hvezdy();

int main() // Definice bezparametrická fce -> parametrická je když má něco za ()
{              // {} fce main je její deklarace
    for (int i = 10; i > 0; i--){
        hvezdy();
     }
}

void vypis()
{
    printf("Hello world\n");
}

// Napiste bezparametrickou fci vypis hvezdy, která  na obrazovku vzpise 10x hvezdy.

void hvezdy()
{
    printf("x");
}
