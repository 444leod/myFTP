/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** unknown_command
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include <sys/select.h>

void unknown_command(client_t client, UNUSED char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
    } else {
        client->current_code = SYNTAX_ERROR;
    }
    client->data_status = WRITING;
}
