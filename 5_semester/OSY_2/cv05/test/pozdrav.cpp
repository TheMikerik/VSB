#include <stdio.h>

#ifndef NAME
// #error Define NAME!
#endif

#define TO_STR( arg ) #arg
#define DEF_TO_STR( arg ) TO_STR( arg )

int g_array[ 1024 * 1024 ] = { 1 };

int main()
{
    printf( "Ahoj " DEF_TO_STR( NAME ) "!\n" );
}