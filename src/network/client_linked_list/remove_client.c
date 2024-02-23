/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** remove_client
*/

#include "clientllist.h"

void remove_client(client_t *clients, int fd)
{
    client_t tmp = *clients;
    client_t prev = NULL;

    if (tmp && tmp->fd == fd) {
        *clients = tmp->next;
        free(tmp);
        return;
    }
    while (tmp && tmp->fd != fd) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp)
        return;
    prev->next = tmp->next;
    free(tmp);
}
