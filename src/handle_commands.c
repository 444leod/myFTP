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

static void execute_command(char **command, client_t client,
    fd_set *readfds, server_info_t server_info)
{
    size_t i = 0;

    for (; commands[i].command; i++) {
        if (strcmp(commands[i].command, command[0]) == 0) {
            commands[i].func(client, command, readfds, server_info);
            return;
        }
    }
    commands[i].func(client, command, readfds, server_info);
}

void handle_command(client_t client, fd_set *readfds,
    server_info_t server_info)
{
    char *command = my_strdup(client->command);
    char **args = str_to_word_array(command, " \t");

    if (client->command)
        my_free(client->command);
    while (args[0] && args[0][0] == '\0')
        args++;
    if (args[0] == NULL || args[0][0] == '\0')
        return;
    execute_command(args, client, readfds, server_info);
    if (client->data_status == WAITING_FOR_FORK)
        return;
    client->data_status = WRITING;
}
