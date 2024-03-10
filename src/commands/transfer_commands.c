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

/**
 * @brief Execute the command of the client
 * @details Execute the command of the client
 *
 * @param client the client to execute the command for
 * @param server_info the server_info
 * @param clientFd the clientFd
 */
static void do_command(client_t client,
    server_info_t server_info, int clientFd)
{
    for (int i = 0; data_commands[i].command; i++) {
        if (strcmp(client->args[0], data_commands[i].command) == 0) {
            data_commands[i].func(client, server_info, clientFd);
            return;
        }
    }
}

/**
 * @brief Passive mode execution
 * @details Passive mode execution (server is waiting for client to connect)
 *
 * @param client the client to execute the passive mode for
 * @param server_info the server_info
 */
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

/**
 * @brief Active mode execution
 * @details Active mode execution (server is connection to client)
 *
 * @param client the client to execute the active mode for
 * @param server_info the server_info
 */
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

/**
 * @brief Execute the mode
 * @details Execute the command based on client's mode (passive or active)
 *
 * @param client the client to execute the mode for
 * @param server_info the server_info
 */
static void execute_mode(client_t client, server_info_t server_info)
{
    switch (client->external_socket->mode) {
        case PASSIVE:
            passive_mode(client, server_info);
            break;
        case ACTIVE:
            active_mode(client, server_info);
            break;
        default:
            break;
    }
}

/**
 * @brief Fork loop
 * @details Fork loop
 *
 * @param client the client to fork
 * @param server_info the server_info
 */
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
        my_exit(0);
    }
}

/**
 * @brief Execute the fork
 * @details Execute the fork
 *
 * @param client the client to execute the fork for
 * @param args the arguments of the command
 * @param server_info the server_info
 */
static void execute_fork(client_t client, char **args,
    server_info_t server_info)
{
    client->args = args;
    fork_loop(client, server_info);
}

/**
 * @brief Check if the transfer command has an error
 * @details Check if the transfer command has an error
 *
 * @param client the client to check the transfer command of
 * @param server_info the server_info
 * @param len the length of the arguments
 *
 * @return true if error, false if not
 */
static bool is_error_case(client_t client, server_info_t server_info,
    int len, char **args)
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
    for (int i = 0; data_commands_verif[i].command; i++)
        if (strcmp(args[0], data_commands_verif[i].command) == 0)
            return data_commands_verif[i].func(client, server_info, args);
    printf("Missing command in verif table\n");
    return true;
}

/**
 * @brief Transfer commands
 * @details Transfer commands of the client
 * Transfer commands of the client, for data transfer (passive and active mode)
 *
 * @param client the client to transfer commands for
 * @param args the arguments of the transfer command
 * @param server_info the server_info
 */
void transfer_commands(client_t client, char **args,
    UNUSED fd_set *readfds, server_info_t server_info)
{
    int len = tablen((void **)args);

    if (is_error_case(client, server_info, len, args))
        return;
    execute_fork(client, args, server_info);
    client->data_status = WAITING_FOR_FORK;
    client->external_socket->mode = NO_MODE;
    client->external_socket->fd = -1;
    client->external_socket->port = -1;
}
