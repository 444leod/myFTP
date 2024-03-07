/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** print_fd_set
*/

#include <stdio.h>
#include <sys/select.h>
#include "debug.h"

void print_fd_set(fd_set *set)
{
    int fds[FD_SETSIZE] = {0};
    int count = 0;

    if (!DEBUG)
        return;
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (FD_ISSET(i, set)) {
            fds[count] = i;
            count++;
        }
    }
    printf("[DEBUG] fds: [");
    for (int i = 0; i < count - 1; ++i)
        printf("%d, ", fds[i]);
    printf("%d]\n", fds[count - 1]);
}
