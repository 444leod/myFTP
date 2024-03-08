/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** noop
*/

#include "ftp.h"
#include "reply_code.h"

void noop(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    (void)args;
    (void)readfds;
    (void)server_info;
    client->current_code = COMMAND_OK;
}
