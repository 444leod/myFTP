/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** commands
*/

#include "commands.h"

/**
 * @brief Commands array
 * @details Array of commands, with their name and function
*/
const command_t commands[] = {
    {"USER", &user},
    {"PASS", &pass},
    {"CWD", &cwd},
    {"CDUP", &cdup},
    {"QUIT", &quit},
    {"DELE", &dele},
    {"PWD", &pwd},
    {"PASV", &pasv},
    {"PORT", &port},
    {"HELP", &help},
    {"NOOP", &noop},
    {"RETR", &transfer_commands},
    {"STOR", &transfer_commands},
    {"LIST", &transfer_commands},
    {"TYPE", &type},
    {NULL, &unknown_command}
};

/**
 * @brief Data commands array
 * @details Array of data commands, with their name and function
*/
const data_command_t data_commands[] = {
    { "LIST", &list },
    { "RETR", &retr },
    { "STOR", &stor },
    { NULL, NULL }
};

/**
 * @brief Data commands verify array
 * @details Array of data commands verificator, with their name and function
*/
const data_command_verify_t data_commands_verif[] = {
    { "LIST", &is_list_error },
    { "RETR", &is_retr_error },
    { "STOR", &is_stor_error },
    { NULL, NULL }
};
