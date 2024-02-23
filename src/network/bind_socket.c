/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** bind_socket
*/

#include "ftp.h"

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
