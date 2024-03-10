/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** create_client
*/

#include "clientllist.h"
#include "ftp.h"

/**
 * @brief Initialize the client buffers
 * @details Initialize the client buffers to NULL
 *
 * @param client the client
*/
static void initialize_client_buffers(client_t client)
{
    client->command = NULL;
    client->username = NULL;
    client->next_commands = NULL;
    client->args = NULL;
    client->buffer = NULL;
}

/**
 * @brief Get the status (dev)
 * @details Get the status of the client
 *
 * @return the status (LOGGED_IN if dev mode, or NOT_LOGGED_IN)
*/
static int get_status(void)
{
    #if DEV_MODE
    return STATUS_LOGGED_IN;
    #else
    return STATUS_NOT_LOGGED_IN;
    #endif
}

/**
 * @brief Create a client
 * @details Create a client with the given fd and ip
 *
 * @param fd the file descriptor
 * @param ip the ip
 *
 * @return the created client
*/
client_t create_client(int fd, char *ip)
{
    client_t client = my_malloc(sizeof(struct client_s));
    static int client_id = 0;

    if (!client)
        my_exit(84);
    initialize_client_buffers(client);
    client->fd = fd;
    client->ip = ip;
    client->next = NULL;
    client->id = client_id;
    client->status = get_status();
    client->data_status = WRITING;
    client->current_code = 220;
    client->pwd = my_strdup("/");
    client->external_socket = create_external_socket();
    client_id++;
    return client;
}
