/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** get_current_dir
*/

#include <unistd.h>
#include <stdio.h>
#include "garbage_collector.h"

char *get_current_dir(void)
{
    char *buffer = my_malloc(sizeof(char) * 1024);
    size_t size = 1024;

    if (getcwd(buffer, size) == NULL) {
        return NULL;
    }
    return buffer;
}
