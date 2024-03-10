/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** help
*/

#include "ftp.h"
#include "reply_code.h"
#include "help.h"

/**
 * @brief Update the help buffer
 * @details Update the help buffer of the client
 * based on the arguments of the command
 *
 * @param client the client to update the help buffer of
 * @param args the arguments of the command
*/
static void update_help_buffer(client_t client, char **args)
{
    if (args[1] == NULL) {
        client->buffer = my_strdup(GLOBAL_HELP_MESSAGE);
        return;
    }
    for (int i = 0; help_list[i].command != NULL; i++) {
        if (strcmp(args[1], help_list[i].command) == 0) {
            client->buffer = my_strdup(help_list[i].description);
            return;
        }
    }
    client->buffer = my_strdup(GLOBAL_HELP_MESSAGE);
}

/**
 * @brief Help command
 * @details Send the help message to the client
 *
 * @param client the client to send the help message to
 * @param args the arguments of the command
*/
void help(client_t client, char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    client->current_code = HELP_MESSAGE;
    update_help_buffer(client, args);
}
