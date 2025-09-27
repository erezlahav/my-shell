CC = gcc
CFLAGS = -Wall -Iheaders
SRC = src/main.c src/parser.c src/utils.c src/pipe.c src/redirection.c src/commands.c
OBJ = $(SRC:.c=.o)
TARGET = my_shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

