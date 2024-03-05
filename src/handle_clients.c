/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_clients
*/

#include "clientllist.h"
#include <sys/select.h>
#include "lib.h"
#include "ftp.h"
#include <unistd.h>
#include <stdio.h>

static void send_buffer(client_t client)
{
    if (client->current_code) {
        reply_code(client->current_code, client->fd);
        client->current_code = 0;
        if (client->next_commands == NULL) {
            client->data_status = READING;
            return;
        }
        if (strstr(client->next_commands, "\r\n") == NULL)
            client->data_status = READING;
        else
            client->data_status = PROCESSING;
    }
}

static void read_buffer(client_t client)
{
    char buffer[1024] = {0};
    int valread = 0;

    valread = read(client->fd, buffer, 1024);
    if (valread == -1)
        my_error(strerror(errno));
    if (valread == 0) {
        remove_client(client->fd);
        return;
    }
    if (valread > 0) {
        if (client->next_commands)
            client->next_commands = supercat(2, client->next_commands, buffer);
        else
            client->next_commands = my_strdup(buffer);
        client->data_status = PROCESSING;
    }
}

static void queue_command(client_t client)
{
    char *after_crlf = NULL;
    int index = 0;

    if (client->next_commands) {
        after_crlf = strstr(client->next_commands, "\r\n");
        if (after_crlf) {
            index = after_crlf - client->next_commands;
            client->command = my_strndup(client->next_commands, index);
            client->next_commands = my_strdup(client->next_commands + index + 2);
        }
    }
}

static void trigger_action(client_t client, fd_set *readfds, fd_set *writefds)
{
    if (FD_ISSET(client->fd, readfds))
        read_buffer(client);
    if (client->data_status == PROCESSING) {
        queue_command(client);
        if (client->command)
            handle_command(client, readfds);
        else
            client->data_status = READING;
        client->command = NULL;
    }
    if (FD_ISSET(client->fd, writefds))
        send_buffer(client);
}

void loop_clients(client_t *clients, fd_set *readfds, fd_set *writefds)
{
    client_t tmp = *clients;
    int tempFd = 0;

    while (tmp) {
        tempFd = tmp->fd;
        trigger_action(tmp, readfds, writefds);
        if (tmp && tmp->fd == tempFd)
            tmp = tmp->next;
    }
}
