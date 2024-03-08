/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** quit
*/

#include "ftp.h"
#include "clientllist.h"
#include "lib.h"
#include "reply_code.h"
#include <sys/select.h>

void quit(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    (void)server_info;
    (void)readfds;
    if (tablen((void **)args) != 1) {
        client->current_code = SYNTAX_ERROR;
        return;
    }
    client->current_code = SERVICE_CLOSING_CONTROL_CONNECTION;
}
