gcc -c output.c -o output.o

ar rcs liboutput.a output.o

gcc main.c -L. -loutput -o program
