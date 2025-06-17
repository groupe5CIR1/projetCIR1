objects = src/c/main.o src/c/print_book.o

all: src/uwu

src/uwu: $(objects)
	gcc -Wall -o src/uwu $(objects)

src/c/main.o: src/c/main.c src/headers/print_book.h
	gcc -Wall -c src/c/main.c -o src/c/main.o

src/c/print_book.o: src/c/print_book.c src/headers/print_book.h
	gcc -Wall -c src/c/print_book.c -o src/c/print_book.o

clean:
	rm -f $(objects) src/uwu src/export/*.html
