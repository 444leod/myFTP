/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** transfer_commands
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include "lib.h"
#include "commands.h"
#include <sys/select.h>
#include <stdbool.h>

static void do_command(client_t client,
    server_info_t server_info, int clientFd)
{
    char **args = str_to_word_array(client->command, " \t");

    for (int i = 0; data_commands[i].command; i++) {
        if (strcmp(args[0], data_commands[i].command) == 0) {
            data_commands[i].func(client, server_info, clientFd);
            return;
        }
    }
}

static void passive_mode(client_t client, server_info_t server_info)
{
    fd_set readfds;
    int clientFd = 0;
    int fd = client->external_socket->fd;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    if (select(fd + 1, &readfds, NULL, NULL, NULL) == -1) {
        client->current_code = CANT_OPEN_DATA_CONNECTION;
        reply_code(client);
        return;
    }
    clientFd = accept(fd, NULL, NULL);
    if (clientFd == -1) {
        client->current_code = CANT_OPEN_DATA_CONNECTION;
        reply_code(client);
        return;
    }
    do_command(client, server_info, clientFd);
}

static void active_mode(client_t client, server_info_t server_info)
{
    struct sockaddr_in servAddr;
    socklen_t servAddrLen = sizeof(servAddr);
    int clientFd = 0;
    char *ip = client->external_socket->ip;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(client->external_socket->port);
    clientFd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFd == -1 ||
        inet_pton(AF_INET, ip, &servAddr.sin_addr) <= 0 ||
        connect(clientFd, (struct sockaddr *)&servAddr, servAddrLen) == -1) {
        client->current_code = CANT_OPEN_DATA_CONNECTION;
        reply_code(client);
        return;
    }
    do_command(client, server_info, clientFd);
}

static void execute_mode(client_t client, server_info_t server_info)
{
    switch (client->external_socket->mode) {
        case PASSIVE:
            passive_mode(client, server_info);
            break;
        case ACTIVE:
            active_mode(client, server_info);
            break;
    }
}

static void fork_loop(client_t client, server_info_t server_info)
{
    int pid = fork();

    client->data_status = WAITING_FOR_FORK;
    if (pid == -1) {
        client->current_code = CANT_OPEN_DATA_CONNECTION;
        return;
    }
    client->external_socket->pid = pid;
    if (pid == 0) {
        execute_mode(client, server_info);
        exit(0);
    }
}

static void execute_fork(client_t client, char **args,
    server_info_t server_info)
{
    client->args = args;
    fork_loop(client, server_info);
}

static bool is_error_case(client_t client, int len)
{
    if (len > 2) {
        client->current_code = SYNTAX_ERROR;
        return true;
    }
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return true;
    }
    if (client->external_socket->mode == NO_MODE) {
        client->current_code = CANT_OPEN_DATA_CONNECTION;
        return true;
    }
    return false;
}

void transfer_commands(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    int len = tablen((void **)args);

    (void)readfds;
    if (is_error_case(client, len))
        return;
    execute_fork(client, args, server_info);
    client->data_status = WAITING_FOR_FORK;
    client->external_socket->mode = NO_MODE;
    client->external_socket->fd = -1;
    client->external_socket->port = -1;
}
