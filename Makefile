##
## EPITECH PROJECT, 2024
## myFTP
## File description:
## Makefile
##

NAME = myftp

SRC = main.c \
	$(addprefix src/, $(SRC_SRC)) \
	$(addprefix src/network/, $(NETWORK_SRC)) \
	$(addprefix src/network/client_linked_list/, $(CLIENT_LLIST_SRC)) \

SRC_SRC = ftp.c \
	check_args.c \
	my_lib.c \

NETWORK_SRC = get_socket.c \
	bind_socket.c \
	listen_socket.c \
	accept_socket.c \
	reply_code.c \

CLIENT_LLIST_SRC = add_client.c \
	create_client.c \
	remove_client.c \

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
