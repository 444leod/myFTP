/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** my_strdup
*/

#include <stdlib.h>
#include <string.h>
#include "garbage_collector.h"

char *my_strdup(char const *src)
{
    char *dest = my_malloc(sizeof(char) * (strlen(src) + 1));

    strcpy(dest, src);
    return dest;
}

char *my_strndup(char const *src, int n)
{
    char *dest = my_malloc(sizeof(char) * (n + 1));

    strncpy(dest, src, n);
    return dest;
}
