/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** lib
*/

#include <stdlib.h>
#include <stdio.h>

void my_error(char *str)
{
    fprintf(stderr, "Error: %s\n", str);
    exit(84);
}
