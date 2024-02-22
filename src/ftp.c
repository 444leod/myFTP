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

    if (errno != 0)
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

int ftp(int argc, char *argv[])
{
    int socketFd = -1;
    server_info_t server_info;

    errno = 0;
    check_args(argc, argv);
    server_info = init_server_info(argv);
    socketFd = get_socket();
    return 0;
}
