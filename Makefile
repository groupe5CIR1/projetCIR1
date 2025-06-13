objects = src/main.o src/print_book.o

all: src/uwu

src/uwu: $(objects)
	gcc -Wall -o src/uwu $(objects)

src/main.o: src/main.c src/print_book.h
	gcc -Wall -c src/main.c -o src/main.o

src/print_book.o: src/print_book.c src/print_book.h
	gcc -Wall -c src/print_book.c -o src/print_book.o

clean:
	rm -f $(objects) src/uwu src/export/*.html
