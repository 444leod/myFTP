/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** my_error
*/

#include "ftp.h"

void my_error(char *str)
{
    fprintf(stderr, "Error: %s\n", str);
    my_exit(84);
}
