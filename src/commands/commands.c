/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** commands
*/

#include "commands.h"

const command_t commands[] = {
    {"USER", &user},
    {"PASS", &pass},
    {"CWD", &cwd},
    {"CDUP", &cdup},
    {"QUIT", &quit},
    // {"DELE", NULL},
    {"PWD", &pwd},
    {"PASV", &pasv},
    // {"PORT", NULL},
    // {"HELP", NULL},
    // {"NOOP", NULL},
    // {"RETR", NULL},
    // {"STOR", NULL},
    {"LIST", &transfer_commands},
    {NULL, &unknown_command}
};

const data_command_t data_commands[] = {
    { "LIST", &list },
    // { "RETR", NULL },
    // { "STOR", NULL },
    { NULL, NULL }
};
