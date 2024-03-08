/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** user
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include "lib.h"
#include "accounts.h"
#include <sys/select.h>

static void verify_user(client_t client, char *username)
{
    if (client->status == STATUS_USERNAME_OK ||
        client->status == STATUS_LOGGED_IN) {
        client->current_code = BAD_COMMAND_SEQUENCE;
        return;
    }
    if (client->username) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    for (int i = 0; accounts[i].username; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            client->username = my_strdup(username);
            client->current_code = USERNAME_OK_NEED_PASSWORD;
            client->status = STATUS_USERNAME_OK;
            return;
        }
    }
    client->status = STATUS_USERNAME_OK;
    client->current_code = USERNAME_OK_NEED_PASSWORD;
}

void user(client_t client, char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    int len = tablen((void **)args);

    switch (len) {
        case 2:
            verify_user(client, args[1]);
            break;
        default:
            client->current_code = SYNTAX_ERROR_IN_PARAMETERS;
            break;
    }
}
