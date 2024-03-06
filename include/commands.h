/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** commands
*/

#pragma once

#include <sys/select.h>

typedef struct command_s {
    char *command;
    void (*func)(client_t client, char **args, fd_set *readfds);
} command_t;

void quit(client_t client, char **args, fd_set *readfds);
void unknown_command(client_t client, char **args, fd_set *readfds);
void user(client_t client, char **args, fd_set *readfds);
void pass(client_t client, char **args, fd_set *readfds);
void pwd(client_t client, char **args, fd_set *readfds);

const command_t commands[] = {
    {"USER", &user},
    {"PASS", &pass},
    // {"CWD", NULL},
    // {"CDUP", NULL},
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
