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

/**
 * @brief Verify the password match
 * @details Verify the password match of the client
 * based on the account password and the password
 *
 * @param client the client to verify the password match of
 * @param account_password the account password
 * @param password the password to verify
 */
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

/**
 * @brief Verify the password
 * @details Verify the password of the client
 * based on the username and the password
 *
 * @param client the client to verify the password of
 * @param password the password to verify
 */
static void verify_password(client_t client, char *password)
{
    if (client->status != STATUS_USERNAME_OK) {
        client->current_code = STATUS_LOGGED_IN;
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

/**
 * @brief Pass command
 * @details Pass command to log in the user
 * if the user is already logged in, the client will receive a user not logged
 * in error
 * if the user has not entered a username, the client will receive a not logged
 * in error
 * if the password is correct, the client will receive a user logged in.
 *
 * @param client the client to execute the command for
 * @param args the arguments of the command
*/
void pass(client_t client, char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    int len = tablen((void **)args);

    switch (len) {
        case 2:
            verify_password(client, args[1]);
            break;
        default:
            client->current_code = SYNTAX_ERROR_IN_PARAMETERS;
            break;
    }
}
