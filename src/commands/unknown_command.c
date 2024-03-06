/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** unknown_command
*/

#include "clientllist.h"
#include <sys/select.h>

void unknown_command(client_t client, char **args, fd_set *readfds)
{
    (void)args;
    (void)readfds;
    client->current_code = 500;
    client->data_status = WRITING;
}
