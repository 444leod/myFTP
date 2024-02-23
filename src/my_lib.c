/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** lib
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void my_clean_exit(int status, int fd)
{
    static int actualFd = -1;

    if (status == -1) {
        actualFd = fd;
        return;
    }
    if (actualFd != -1)
        close(actualFd);
    exit(status);
}

void my_exit(int status)
{
    my_clean_exit(status, 0);
}

void prepare_exit(int socketFd)
{
    my_clean_exit(-1, socketFd);
}

void my_error(char *str)
{
    fprintf(stderr, "Error: %s\n", str);
    my_exit(84);
}
