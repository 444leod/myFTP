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

static char *get_pasv_port(int port)
{
    int p1 = port / 256;
    int p2 = port % 256;

    return my_snprintf("%d,%d", p1, p2);
}

static void update_client_buffer(client_t client, server_info_t server_info)
{
    char *port_str = get_pasv_port(client->external_socket->port);

    client->buffer = supercat(3, server_info->ip, ",", port_str);
    client->buffer = replace_char(client->buffer, '.', ',');
}

static void create_data_socket(client_t client)
{
    client->external_socket->fd = get_socket();
    bind_socket(client->external_socket->fd, 0, &client->external_socket->ip);
    get_port(client->external_socket->fd, &client->external_socket->port);
    listen_socket(client->external_socket->fd, 1);
}

void pasv(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    (void)args;
    (void)readfds;
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    client->current_code = ENTERING_PASSIVE_MODE;
    client->external_socket->mode = PASSIVE;
    create_data_socket(client);
    update_client_buffer(client, server_info);
    if (DEBUG)
        printf("port: %d\n", client->external_socket->port);
}
