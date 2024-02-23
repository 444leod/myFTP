/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_clients
*/

#include "clientllist.h"
#include "ftp.h"

static void handle_client(client_t client, fd_set *readfds)
{
    char buffer[1024] = {0};
    int valread = 0;

    valread = read(client->fd, buffer, 1024);
    if (valread < 0)
        my_error(strerror(errno));
    if (strcmp(buffer, "QUIT\r\n") == 0) {
        write(client->fd, "221 Service closing control connection.", 38);
        printf("client %d disconnected\n", client->id);
        FD_CLR(client->fd, readfds);
        remove_client(client->fd);
        return;
    }
    buffer[valread - 2] = '\0';
    printf("client message: \"%s\"\n", buffer);
    dprintf(client->fd, "Server received: %s\n", buffer);
}

void loop_clients(client_t *clients, fd_set *readfds)
{
    client_t tmp = *clients;
    int tempFd = 0;

    while (tmp) {
        tempFd = tmp->fd;
        if (FD_ISSET(tmp->fd, readfds)) {
            handle_client(tmp, readfds);
        }
        if (tmp && tmp->fd == tempFd)
            tmp = tmp->next;
    }
}
