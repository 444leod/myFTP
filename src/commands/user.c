/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** user
*/

#include "clientllist.h"
#include "ftp.h"
#include "reply_code.h"
#include "accounts.h"

static void verify_user(client_t client, char *username)
{
    if (client->status == STATUS_USERNAME_OK) {
        client->current_code = 503;
        return;
    }
    if (client->username) {
        client->current_code = 530;
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
    client->current_code = 530;
}

void user(client_t client, char **args, fd_set *readfds)
{
    (void)readfds;
    int len = tablen((void **)args);

    switch (len) {
        case 2:
            verify_user(client, args[1]);
            break;
        default:
            client->current_code = SYNTAX_ERROR;
            break;
    }
}
