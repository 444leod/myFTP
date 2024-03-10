/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** create_external_socket
*/

#include "clientllist.h"
#include "garbage_collector.h"
#include <netinet/in.h>

/**
 * @brief Create an external socket struct
 * @details Create an external socket struct with default values
 * for better fork handling
 *
 * @return external_socket_t the created external socket
*/
external_socket_t create_external_socket(void)
{
    external_socket_t new_socket = my_malloc(sizeof(struct external_socket_s));

    new_socket->fd = 0;
    new_socket->ip = my_malloc(sizeof(char) * INET_ADDRSTRLEN + 1);
    new_socket->ip[INET_ADDRSTRLEN] = '\0';
    new_socket->command = NULL;
    new_socket->port = -1;
    new_socket->mode = NO_MODE;
    return new_socket;
}
