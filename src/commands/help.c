/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** help
*/

#include "ftp.h"
#include "reply_code.h"
#include "help.h"

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

void help(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    (void)readfds;
    (void)server_info;
    client->current_code = HELP_MESSAGE;
    update_help_buffer(client, args);
}
