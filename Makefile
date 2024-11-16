CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = lsh

all: $(TARGET)

$(TARGET): src/shell.c
	$(CC) $(CFLAGS) -o $(TARGET) src/shell.c

clean:
	rm -f $(TARGET)