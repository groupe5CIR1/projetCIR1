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

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run