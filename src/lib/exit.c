/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** exit
*/

#include <stdlib.h>
#include <unistd.h>
#include "ftp.h"

static void my_clean_exit(int status, int fd)
{
    static int actualFd = -1;

    if (status == -1) {
        actualFd = fd;
        return;
    }
    if (actualFd != -1)
        close(actualFd);
    clear_clients();
    my_free_all();
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
