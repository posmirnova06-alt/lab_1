CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c matrix.c int_field.c double_field.c 
OBJ = $(SRC:.c=.o)

program: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o program

clean:
	rm -f *.o program
