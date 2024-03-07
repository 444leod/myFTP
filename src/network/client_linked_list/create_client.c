/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** create_client
*/

#include "clientllist.h"
#include "ftp.h"

client_t create_client(int fd, char *ip)
{
    client_t client = my_malloc(sizeof(struct client_s));
    static int client_id = 0;

    if (!client)
        my_exit(84);
    client->fd = fd;
    client->ip = ip;
    client->next = NULL;
    client->id = client_id;
    client->status = STATUS_NOT_LOGGED_IN;
    client->mode = NONE;
    client->data_status = WRITING;
    client->current_code = 220;
    client->command = NULL;
    client->username = NULL;
    client->next_commands = NULL;
    client->pwd = my_strdup("/");
    client_id++;
    return client;
}
