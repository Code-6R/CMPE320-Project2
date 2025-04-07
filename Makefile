wzip: main.o
	gcc -o wzip main.o

main.o: main.c
	gcc -c main.c

