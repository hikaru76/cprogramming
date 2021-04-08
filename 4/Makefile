program: main.o matrix.o
	gcc -o program main.o matrix.o

main.o: main.c matrix.h
	gcc -c main.c

matrix.o: matrix.c matrix.h
	gcc -c matrix.c