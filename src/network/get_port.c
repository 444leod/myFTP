/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** get_port
*/

#include "lib.h"
#include <arpa/inet.h>

void get_port(int fd, int *port)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(fd, (struct sockaddr *)&sin, &len) == -1)
        my_error("getsockname");
    *port = ntohs(sin.sin_port);
}
