/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** noop
*/

#include "ftp.h"
#include "reply_code.h"

/**
 * @brief No operation
 * @details Do nothing
 *
 * @param client the client to do nothing for
*/
void noop(client_t client, UNUSED char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    client->current_code = COMMAND_OK;
}
