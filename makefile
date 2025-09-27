CC = gcc
CFLAGS = -Wall
SRC = main.c parser.c utils.c pipe.c redirection.c commands.c
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
