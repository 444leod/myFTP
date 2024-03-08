/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** commands
*/

#pragma once

#include <sys/select.h>
#include "ftp.h"

typedef struct command_s {
    char *command;
    void (*func)(client_t, char **, fd_set *, server_info_t);
} command_t;

typedef struct data_command_s {
    char *command;
    void (*func)(client_t client, server_info_t server_info, int clientFd);
} data_command_t;

void quit(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void unknown_command(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void user(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void pass(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void pwd(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void cwd(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void cdup(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void pasv(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void transfer_commands(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);

void list(client_t client, server_info_t server_info, int clientFd);

extern const command_t commands[];
extern const data_command_t data_commands[];
