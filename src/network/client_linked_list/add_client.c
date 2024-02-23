/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** add_client
*/

#include "clientllist.h"

void add_client(client_t new_client)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;

    if (!tmp) {
        *clients = new_client;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_client;
}
