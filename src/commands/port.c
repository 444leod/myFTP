/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** port
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include "lib.h"
#include "debug.h"
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief Is number
 * @details Check if the string is a number
 *
 * @param str the string to check
 * @return true if the string is a number
 */
static bool is_number(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

/**
 * @brief Verify ip
 * @details Verify ip of the client
 *
 * @param items the items to verify the ip of
 * @return true if the ip is correct
 */
static bool verify_ip(char **items)
{
    for (int i = 0; items[i]; i++) {
        if (!is_number(items[i]))
            return false;
        if (atoi(items[i]) < 0 || atoi(items[i]) > 255)
            return false;
    }
    return true;
}

/**
 * @brief Get full arg
 * @details Get full arg of the command as h1,h2,h3,h4,p1,p2
 *
 * @param arg the arg to get the full arg of
 * @return char* the full arg
 */
static char *get_full_arg(char *arg)
{
    char *full_arg = arg;

    if (arg[0] == '(')
        full_arg++;
    if (full_arg[strlen(full_arg) - 1] == ')')
        full_arg[strlen(full_arg) - 1] = '\0';
    return full_arg;
}

/**
 * @brief Connect to client
 * @details Connect to client of the client
 *
 * @param client the client to connect to
 * @param args the arguments of the connect to client command
 * @return int 0 if success, -1 if error
 */
static int connect_to_client(client_t client, char **args)
{
    char *full_arg = get_full_arg(args[1]);
    char **items = NULL;

    if (full_arg == NULL)
        return -1;
    items = str_to_word_array(full_arg, ",");
    if (items == NULL || tablen((void **)items) != 6)
        return -1;
    if (!verify_ip(items))
        return -1;
    client->external_socket->ip =
        my_snprintf("%s.%s.%s.%s", items[0], items[1], items[2], items[3]);
    client->external_socket->port = atoi(items[4]) * 256 + atoi(items[5]);
    return 0;
}

/**
 * @brief Port command
 * @details Port command of the client
 * Open a data socket and bind it to the client ip and port
 *
 * @param client the client to port
 * @param args the arguments of the port command
 */
void port(client_t client, char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    if (tablen((void **)args) != 2) {
        client->current_code = SYNTAX_ERROR;
        return;
    }
    if (connect_to_client(client, args) == -1) {
        client->current_code = CANT_OPEN_DATA_CONNECTION;
        return;
    }
    client->current_code = COMMAND_OK;
    client->external_socket->mode = ACTIVE;
    DEBUG_PRINT("ip: %s\n", client->external_socket->ip);
    DEBUG_PRINT("port: %d\n", client->external_socket->port);
}
