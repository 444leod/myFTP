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

void user(client_t client, char **args, fd_set *readfds);
void quit(client_t client, char **args, fd_set *readfds);
void unknown_command(client_t client, char **args, fd_set *readfds);

const command_t commands[] = {
    {"USER", &user},
    // {"PASS", NULL},
    // {"CWD", NULL},
    // {"CDUP", NULL},
    {"QUIT", &quit},
    // {"DELE", NULL},
    // {"PWD", NULL},
    // {"PASV", NULL},
    // {"PORT", NULL},
    // {"HELP", NULL},
    // {"NOOP", NULL},
    // {"RETR", NULL},
    // {"STOR", NULL},
    // {"LIST", NULL},
    {NULL, &unknown_command}
};
