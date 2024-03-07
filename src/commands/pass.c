/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** pass
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include "accounts.h"
#include "lib.h"
#include <sys/select.h>

static void verify_password_match(client_t client, char *account_password,
    char *password)
{
    if (strcmp(account_password, password) == 0) {
        client->current_code = USER_LOGGED_IN;
        client->status = STATUS_LOGGED_IN;
    } else {
        client->current_code = NOT_LOGGED_IN;
    }
}

static void verify_password(client_t client, char *password)
{
    if (client->status != STATUS_USERNAME_OK) {
        client->current_code = BAD_COMMAND_SEQUENCE;
        return;
    }
    if (client->username == NULL) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    for (int i = 0; accounts[i].username; i++) {
        if (strcmp(accounts[i].username, client->username) == 0) {
            verify_password_match(client, accounts[i].password, password);
            return;
        }
    }
    client->current_code = NOT_LOGGED_IN;
}

void pass(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    int len = tablen((void **)args);

    (void)server_info;
    (void)readfds;
    switch (len) {
        case 2:
            verify_password(client, args[1]);
            break;
        default:
            client->current_code = SYNTAX_ERROR_IN_PARAMETERS;
            break;
    }
}
