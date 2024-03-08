/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** get_socket
*/

#include <arpa/inet.h>
#include "lib.h"

int get_socket(void)
{
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (errno != 0 || socketFd == -1)
        my_error(supercat(2, "get socket failed: ", strerror(errno)));
    return socketFd;
}
