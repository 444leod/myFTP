/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** supercat
*/

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "garbage_collector.h"

static char *my_strcat(char *dest, char *src)
{
    char *tmp = my_malloc(strlen(dest) + strlen(src) + 1);

    strcpy(tmp, dest);
    strcat(tmp, src);
    return tmp;
}

/**
 * @brief Concatenate multiple strings
 * @details Concatenate multiple strings into one using va_args
 *
 * @param n the number of strings to concatenate
 * @param ... the strings to concatenate
 *
 * @return the concatenated string
*/
char *supercat(int n, ...)
{
    va_list ap;
    char *str = my_strdup("");
    char *tmp = NULL;

    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        tmp = va_arg(ap, char *);
        str = my_strcat(str, tmp);
    }
    va_end(ap);
    return str;
}
