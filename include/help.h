/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** help
*/

#pragma once

#include <stddef.h>

typedef struct help_s {
    char *command;
    char *description;
} help_t;

/**
 * @brief help message list
 * @details list of help messages for each command
*/
static const help_t help_list[] = {
    {"USER", "USER <sp> <username> <CRLF> (send username)."},
    {"PASS", "PASS <sp> <password> <CRLF> (send password)."},
    {"CWD", "CWD <sp> <pathname> <CRLF> (change working directory)."},
    {"CDUP", "CDUP <CRLF> (change to parent directory)."},
    {"QUIT", "QUIT <CRLF> (terminate connection)."},
    {"DELE", "DELE <sp> <pathname> <CRLF> (delete file)."},
    {"PWD", "PWD <CRLF> (print working directory)."},
    {"PASV", "PASV <CRLF> (enter passive mode)."},
    {"PORT", "PORT <sp> <host-port> <CRLF> (open data port)."},
    {"HELP", "HELP [<sp> <string>] <CRLF> (return help information)."},
    {"NOOP", "NOOP <CRLF> (do nothing)."},
    {"RETR", "RETR <sp> <pathname> <CRLF> (retrieve file)."},
    {"STOR", "STOR <sp> <pathname> <CRLF> (store file)."},
    {"LIST", "LIST [<sp> <pathname>] <CRLF> (list files,"
        "need either passive or active mode)."},
    // {"SYST", "Get operating system type of server"},
    // {"MKD", "Make directory"},
    {NULL, NULL}
};

/**
 * @brief global help message
 * @details global help message if no command is specified or unknown
 * command is specified
*/
static const char *GLOBAL_HELP_MESSAGE = "The following commands are "
"recognized: \nCDUP CWD  DELE HELP LIST NOOP PASS PASV PORT PWD  QUIT "
"RETR STOR USER";
