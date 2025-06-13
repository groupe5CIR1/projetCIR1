all: uwu clean

uwu: main.o print_book.o
	gcc -Wall -o uwu main.o print_book.o

main.o: main.c print_book.h
	gcc -Wall -c main.c

print_book.o: print_book.c print_book.h
	gcc -Wall -c print_book.c

clean:
	rm -f *.o uwu
