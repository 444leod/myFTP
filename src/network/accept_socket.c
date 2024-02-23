/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** accept_client
*/

#include "ftp.h"

void accept_socket(int sockFd, void (*func)(int))
{
    int clientFd = 0;
    struct sockaddr_in clientAddress;
    socklen_t len = sizeof(clientAddress);

    clientFd = accept(sockFd, (struct sockaddr *)&clientAddress, &len);
    if (clientFd < 0)
        my_error(strerror(errno));
    func(clientFd);
}