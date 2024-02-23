/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** ftp
*/

#include "ftp.h"
#include "clientllist.h"

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
    server_info->path = strdup(argv[2]);
    return server_info;
}

static void add_clients_to_set(client_t *clients, fd_set *readfds, int *max_sd)
{
    client_t tmp = *clients;

    while (tmp) {
        FD_SET(tmp->fd, readfds);
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
        *clients = create_client(new_socket,
            inet_ntoa(address.sin_addr), NULL, NULL);
    else
        add_client(create_client(new_socket,
            inet_ntoa(address.sin_addr), NULL, NULL));
    reply_code(220, new_socket);
}

void ftp_loop(int socketFd)
{
    fd_set readfds;
    int max_sd = 0;
    client_t *clients = NULL;

    while (1) {
        clients = get_clients();
        FD_ZERO(&readfds);
        FD_SET(socketFd, &readfds);
        max_sd = socketFd;
        add_clients_to_set(clients, &readfds, &max_sd);
        print_fd_set(&readfds);
        if (select(max_sd + 1, &readfds, NULL, NULL, NULL) < 0) {
            my_error(strerror(errno));
        }
        if (FD_ISSET(socketFd, &readfds))
            add_new_client(socketFd);
        loop_clients(clients, &readfds);
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
    ftp_loop(socketFd);
    close(socketFd);
    return 0;
}
