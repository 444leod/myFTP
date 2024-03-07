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
    void (*func)(client_t , char **, fd_set *, server_info_t);
} command_t;

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

const command_t commands[] = {
    {"USER", &user},
    {"PASS", &pass},
    {"CWD", &cwd},
    {"CDUP", &cdup},
    {"QUIT", &quit},
    // {"DELE", NULL},
    {"PWD", &pwd},
    // {"PASV", NULL},
    // {"PORT", NULL},
    // {"HELP", NULL},
    // {"NOOP", NULL},
    // {"RETR", NULL},
    // {"STOR", NULL},
    // {"LIST", NULL},
    {NULL, &unknown_command}
};
