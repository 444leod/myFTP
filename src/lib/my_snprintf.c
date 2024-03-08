/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** my_snprintf
*/

#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include "garbage_collector.h"

char *my_snprintf(const char *format, ...)
{
    va_list args;
    va_list copy;
    int size = 0;
    char *str = NULL;

    va_start(args, format);
    va_copy(copy, args);
    size = vsnprintf(NULL, 0, format, copy);
    va_copy(copy, args);
    if (size < 0)
        return NULL;
    str = my_malloc((size + 1) * sizeof(char));
    vsnprintf(str, size + 1, format, copy);
    va_end(args);
    return str;
}
