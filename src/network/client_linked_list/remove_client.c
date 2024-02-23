/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** remove_client
*/

#include "clientllist.h"
#include <unistd.h>

void remove_client(int fd)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    client_t prev = NULL;

    if (tmp && tmp->fd == fd) {
        *clients = tmp->next;
        close(fd);
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
