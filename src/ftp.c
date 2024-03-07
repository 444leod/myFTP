/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** ftp
*/

#include "ftp.h"
#include "clientllist.h"
#include "lib.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

static void handle_sigint(int sig)
{
    (void)sig;
    my_exit(0);
}

static server_info_t init_server_info(char *argv[])
{
    server_info_t server_info = my_malloc(sizeof(struct server_info_s));

    if (!server_info)
        my_exit(84);
    server_info->port = atoi(argv[1]);
    server_info->path = get_current_dir();
    if (server_info->path == NULL)
        my_error("get_current_dir failed");
    if (server_info->path[strlen(server_info->path) - 1] == '/')
        server_info->path[strlen(server_info->path) - 1] = '\0';
    return server_info;
}

static void add_clients_to_set(
    client_t *clients,
    fd_set *readfds,
    fd_set *writefds,
    int *max_sd)
{
    client_t tmp = *clients;

    while (tmp) {
        if (tmp->data_status == READING)
            FD_SET(tmp->fd, readfds);
        if (tmp->data_status == WRITING)
            FD_SET(tmp->fd, writefds);
        if (tmp->fd > *max_sd)
            *max_sd = tmp->fd;
        tmp = tmp->next;
    }
}

static void add_new_client(int socketFd)
{
    int new_socket = 0;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    client_t *clients = get_clients();

    new_socket = accept(socketFd, (struct sockaddr *)&address,
        (socklen_t *)&addrlen);
    if (new_socket < 0)
        my_error(strerror(errno));
    if (*clients == NULL)
        *clients = create_client(new_socket, inet_ntoa(address.sin_addr));
    else
        add_client(create_client(new_socket, inet_ntoa(address.sin_addr)));
}

static void select_wrapper(int max_sd, fd_set *readfds,
    fd_set *writefds, client_t *clients)
{
    struct timeval timeout = {0, 100};
    int activity = 0;
    client_t tmp = *clients;
    char is_blocking = 1;

    while (tmp) {
        if (tmp->data_status == PROCESSING) {
            is_blocking = 0;
            break;
        }
        tmp = tmp->next;
    }
    if (is_blocking)
        activity = select(max_sd + 1, readfds, writefds, NULL, NULL);
    else
        activity = select(max_sd + 1, readfds, writefds, NULL, &timeout);
    if (activity < 0)
        my_error(strerror(errno));
}

void ftp_loop(int socketFd, server_info_t server_info)
{
    fd_set readfds;
    fd_set writefds;
    int max_sd = 0;
    client_t *clients = NULL;

    while (1) {
        clients = get_clients();
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(socketFd, &readfds);
        max_sd = socketFd;
        add_clients_to_set(clients, &readfds, &writefds, &max_sd);
        print_fd_set(&readfds);
        select_wrapper(max_sd + 1, &readfds, &writefds, clients);
        if (FD_ISSET(socketFd, &readfds))
            add_new_client(socketFd);
        loop_clients(clients, &readfds, &writefds, server_info);
    }
}

int ftp(int argc, char *argv[])
{
    int socketFd = -1;
    server_info_t server_info;

    errno = 0;
    signal(2, handle_sigint);
    check_args(argc, argv);
    server_info = init_server_info(argv);
    socketFd = get_socket();
    prepare_exit(socketFd);
    bind_socket(socketFd, server_info->port);
    listen_socket(socketFd, 1024);
    ftp_loop(socketFd, server_info);
    close(socketFd);
    return 0;
}
