##
## EPITECH PROJECT, 2024
## myFTP
## File description:
## Makefile
##

NAME = myftp

SRC = main.c \
	$(addprefix src/, $(SRC_FOLDER_SRC))

SRC_FOLDER_SRC = ftp.c \
	check_args.c \
	lib.c \

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Wpedantic -I./include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: all

run: all

.PHONY: all clean fclean re
.SILENT: run
