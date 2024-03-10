##
## EPITECH PROJECT, 2024
## myFTP
## File description:
## Makefile
##

NAME = myftp

SRC = main.c \
	$(addprefix src/, $(SRC_SRC)) \
	$(addprefix src/lib/, $(LIB_SRC)) \
	$(addprefix src/network/, $(NETWORK_SRC)) \
	$(addprefix src/network/client_linked_list/, $(CLIENT_LLIST_SRC)) \
	$(addprefix src/commands/, $(COMMANDS_SRC)) \

SRC_SRC = ftp.c \
	check_args.c \
	handle_clients.c \
	handle_commands.c \
	accounts.c \

LIB_SRC = exit.c \
	my_error.c \
	garbage_collector.c \
	garbage_llist.c \
	my_strdup.c \
	str_to_word_array.c \
	tablen.c \
	supercat.c \
	get_current_dir.c \
	my_snprintf.c \
	replace_char.c \
	debug_print.c \

COMMANDS_SRC = commands.c \
	user.c \
	quit.c \
	unknown_command.c \
	pass.c \
	pwd.c \
	cwd.c \
	cdup.c \
	pasv.c \
	list.c \
	transfer_commands.c \
	noop.c \
	dele.c \
	help.c \
	retr.c \
	stor.c \
	type.c \
	port.c \

NETWORK_SRC = get_socket.c \
	bind_socket.c \
	listen_socket.c \
	accept_socket.c \
	reply_code.c \
	print_fd_set.c \
	get_port.c \

CLIENT_LLIST_SRC = add_client.c \
	create_client.c \
	remove_client.c \
	get_clients.c \
	clear_clients.c \
	create_external_socket.c \

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

debug:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g

dev:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g -DDEV_MODE

.PHONY: all clean fclean re
.SILENT: run
