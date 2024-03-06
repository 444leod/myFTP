/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_commands
*/

#include "clientllist.h"
#include <sys/select.h>
#include "commands.h"
#include "lib.h"
#include "ftp.h"
#include <unistd.h>
#include <stdio.h>

static void execute_command(char **command, client_t client, fd_set *readfds)
{
    size_t i = 0;
    for (; commands[i].command; i++) {
        if (strcmp(commands[i].command, command[0]) == 0) {
            commands[i].func(client, command, readfds);
            return;
        }
    }
    // commands[i].func(client, command, readfds);
    client->current_code = 500;
}

void handle_command(client_t client, fd_set *readfds)
{
    char *command = my_strdup(client->command);
    char **args = str_to_word_array(command, " \t");

    free(client->command);
    execute_command(args, client, readfds);
    client->data_status = WRITING;
}
