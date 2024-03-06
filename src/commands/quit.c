/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** quit
*/

#include "clientllist.h"
#include "ftp.h"
#include "reply_code.h"

void quit(client_t client, char **args, fd_set *readfds)
{
    (void)readfds;
    if (tablen((void **)args) != 1) {
        client->current_code = SYNTAX_ERROR;
        return;
    }
    client->current_code = SERVICE_CLOSING_CONTROL_CONNECTION;
    remove_client(client->fd);
}
