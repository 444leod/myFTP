/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** print_fd_set
*/

#include <stdio.h>
#include <sys/select.h>
#include "debug.h"
#include "macros.h"

/**
 * @brief Print a fd_set (debug)
 * @details Print a fd_set (only in dev mode)
 *
 * @param set the fd_set to print
*/
UNUSED static void dev_print_fd_set(fd_set *set)
{
    int fds[FD_SETSIZE] = {0};
    int count = 0;
    char buffer[1024];
    int offset = 0;
    UNUSED static int print = 0;

    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (FD_ISSET(i, set)) {
            fds[count] = i;
            count++;
        }
    }
    offset += sprintf(buffer + offset, "[DEBUG] fds: [");
    for (int i = 0; i < count - 1; ++i)
        offset += sprintf(buffer + offset, "%d, ", fds[i]);
    offset += sprintf(buffer + offset, "%d]\n", fds[count - 1]);
    SOMETIMES_DEBUG(&print, 5000, "%s", buffer);
}

/**
 * @brief Print a fd_set (debug)
 * @details Print a fd_set (only in dev mode)
 *
 * @param set the fd_set to print
*/
void print_fd_set(UNUSED fd_set *set)
{
    #ifndef DEV_MODE
    #else
    dev_print_fd_set(set);
    #endif
}
