/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** unknown_command
*/

#include "clientllist.h"
#include "reply_code.h"
#include <sys/select.h>

void unknown_command(client_t client, char **args, fd_set *readfds)
{
    (void)args;
    (void)readfds;
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
    } else {
        client->current_code = SYNTAX_ERROR;
    }
    client->data_status = WRITING;
}
