/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** type
*/

#include "ftp.h"
#include "reply_code.h"
#include "clientllist.h"
#include <sys/select.h>

void type(client_t client, UNUSED char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    client->current_code = COMMAND_OK;
}
