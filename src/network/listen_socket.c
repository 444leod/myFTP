/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** listen_socket
*/

#include "ftp.h"

void listen_socket(int socketFd, int maxClients)
{
    int listenRes = listen(socketFd, maxClients);

    if (listenRes == -1 || errno != 0)
        my_error(strerror(errno));
}
