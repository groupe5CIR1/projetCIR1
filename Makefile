# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iheaders

# Source files
SRC = src/c/main.c src/c/print_book.c src/c/logic.c src/c/chapters.c \
      src/c/display.c src/c/entity.c src/c/inventory.c src/c/armor.c \
      src/c/entityArray.c src/c/itemArray.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = server

# Default target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Special rule for chapters.c to avoid circular dependencies
src/c/chapters.o: src/c/chapters.c src/headers/chapters.h src/headers/entity.h src/headers/itemArray.h
	$(CC) $(CFLAGS) -c -o $@ $<

# General rule for other .c files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target - removes object files, executable, and HTML files in export directory
clean:
	rm -f $(OBJ) $(TARGET)
	rm -f src/export/*.html

# Run target
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run