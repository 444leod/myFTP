/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** debug_print
*/

#include <stdarg.h>
#include <stdio.h>

void debug_print(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

static void debug_print_va(const char *fmt, va_list args)
{
    vfprintf(stderr, fmt, args);
}

void debug_print_counter(int *counter, int variation, const char *fmt, ...)
{
    va_list args;

    (*counter)++;
    if (*counter % variation == 0) {
        va_start(args, fmt);
        debug_print_va(fmt, args);
        va_end(args);
        (*counter) = 0;
    }
}
