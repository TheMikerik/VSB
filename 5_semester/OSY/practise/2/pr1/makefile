all:
	gcc -c output.c && ar rcs liboutput.a output.o
	gcc main.c -L. -loutput -o main