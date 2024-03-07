/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** pwd
*/

#include "ftp.h"
#include "reply_code.h"
#include "clientllist.h"
#include <sys/select.h>

void pwd(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    (void)server_info;
    (void)args;
    (void)readfds;
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    client->current_code = PATHNAME_CREATED;
    client->data_status = WRITING;
}
