/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** pasv
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include "lib.h"
#include "debug.h"
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Get the pasv port
 * @details Get the pasv port of the client
 *
 * @param port the port to get the pasv port of
 * @return the pasv port
 */
static char *get_pasv_port(int port)
{
    int p1 = port / 256;
    int p2 = port % 256;

    return my_snprintf("%d,%d", p1, p2);
}

/**
 * @brief Update the client buffer
 * @details Update the client buffer with the ip and port
 *
 * @param client the client to update the buffer of
 * @param server_info the server_info
 */
static void update_client_buffer(client_t client, server_info_t server_info)
{
    char *port_str = get_pasv_port(client->external_socket->port);

    client->buffer = supercat(3, server_info->ip, ",", port_str);
    client->buffer = replace_char(client->buffer, '.', ',');
}

/**
 * @brief Create a data socket
 * @details Create a data socket for the client
 *
 * @param client the client to create the data socket for
 */
static void create_data_socket(client_t client)
{
    client->external_socket->fd = get_socket();
    bind_socket(client->external_socket->fd, 0, &client->external_socket->ip);
    get_port(client->external_socket->fd, &client->external_socket->port);
    listen_socket(client->external_socket->fd, 1);
}

/**
 * @brief Pasv command
 * @details Enter passive mode
 * Open a data socket and send the ip and port to the client
 *
 * @param client the client to enter passive mode
 * @param server_info the server_info
 */
void pasv(client_t client, UNUSED char **args,
    UNUSED fd_set *readfds, server_info_t server_info)
{
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    client->current_code = ENTERING_PASSIVE_MODE;
    client->external_socket->mode = PASSIVE;
    create_data_socket(client);
    update_client_buffer(client, server_info);
    DEBUG_PRINT("port: %d\n", client->external_socket->port);
}
