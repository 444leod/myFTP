/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** ftp
*/

#include "ftp.h"

int get_socket(void)
{
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (errno != 0 || socketFd == -1)
        my_error(strerror(errno));
    return socketFd;
}

server_info_t init_server_info(char *argv[])
{
    server_info_t server_info = malloc(sizeof(server_info_t));

    server_info->port = atoi(argv[1]);
    server_info->path = argv[2];
    return server_info;
}

void bind_socket(int socketFd, int portNumber)
{
    struct sockaddr_in serverAddress;
    int bindRes = 0;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
    bindRes = bind(socketFd, (const struct sockaddr *)&serverAddress,
        sizeof(serverAddress));
    if (bindRes == -1 || errno != 0)
        my_error(strerror(errno));
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
    close(socketFd);
    return 0;
}
