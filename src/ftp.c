/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** ftp
*/

#include "ftp.h"

static server_info_t init_server_info(char *argv[])
{
    server_info_t server_info = malloc(sizeof(server_info_t));

    server_info->port = atoi(argv[1]);
    server_info->path = argv[2];
    return server_info;
}

static void handle_client(int clientFd)
{
    char buffer[1024] = {0};
    int valread = 0;

    valread = read(clientFd, buffer, 1024);
    if (valread < 0)
        my_error(strerror(errno));
    buffer[valread - 1] = '\0';
    printf("client message: \"%s\"\n", buffer);
    send(clientFd, "Hello, World!\n", 14, 0);
    close(clientFd);
}

int ftp(int argc, char *argv[])
{
    int socketFd = -1;
    server_info_t server_info;

    errno = 0;
    check_args(argc, argv);
    server_info = init_server_info(argv);
    socketFd = get_socket();
    bind_socket(socketFd, server_info->port);
    listen_socket(socketFd, 1024);
    accept_socket(socketFd, handle_client);
    close(socketFd);
    return 0;
}
