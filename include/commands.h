/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** commands
*/

#pragma once

#include <sys/select.h>
#include "ftp.h"
#include <stdbool.h>

typedef struct command_s {
    char *command;
    void (*func)(client_t, char **, fd_set *, server_info_t);
} command_t;

typedef struct data_command_s {
    char *command;
    void (*func)(client_t client, server_info_t server_info, int clientFd);
} data_command_t;

typedef struct data_command_verify_s {
    char *command;
    bool (*func)(client_t client, server_info_t server_info, char **args);
} data_command_verify_t;

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
void dele(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void help(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void noop(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void type(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);
void port(client_t client, char **args,
    fd_set *readfds, server_info_t server_info);

void list(client_t client, server_info_t server_info, int clientFd);
bool is_list_error(client_t client, server_info_t server_info, char **args);
void retr(client_t client, server_info_t server_info, int clientFd);
bool is_retr_error(client_t client, server_info_t server_info, char **args);
void stor(client_t client, server_info_t server_info, int clientFd);
bool is_stor_error(client_t client, server_info_t server_info, char **args);

extern const command_t commands[];
extern const data_command_t data_commands[];
extern const data_command_verify_t data_commands_verif[];
