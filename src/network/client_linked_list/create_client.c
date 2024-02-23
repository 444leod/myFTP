/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** create_client
*/

#include "clientllist.h"
#include "ftp.h"

client_t create_client(int fd, char *ip, char *username, char *password)
{
    client_t client = malloc(sizeof(client_t));
    static int client_id = 0;

    if (!client)
        my_exit(84);
    client->fd = fd;
    client->ip = ip;
    client->username = username;
    client->password = password;
    client->next = NULL;
    client->id = client_id;
    client_id++;
    return client;
}
