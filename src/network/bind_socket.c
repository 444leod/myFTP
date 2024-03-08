/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** bind_socket
*/

#include <arpa/inet.h>
#include "lib.h"
#include "ftp.h"

void bind_socket(int socketFd, int port, char **ip)
{
    struct sockaddr_in serverAddress;
    int bindRes = 0;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
    bindRes = bind(socketFd, (const struct sockaddr *)&serverAddress,
        sizeof(serverAddress));
    if (bindRes == -1 || errno != 0)
        my_error("bind failed");
    inet_ntop(AF_INET, &(serverAddress.sin_addr),
        *ip, INET_ADDRSTRLEN);
}
