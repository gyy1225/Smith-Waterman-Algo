all: prob2 clean

prob2: main.o
	gcc -ggdb main.o -o prob2 
main.o: main.c
	gcc -ggdb main.c -c
clean:
	rm -rf prob2.o
