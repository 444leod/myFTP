/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** my_error
*/

#include "ftp.h"

/**
 * @brief Print an error message and exit the program
 * @details Print an error message and exit the program
 *
 * @param str the error message
*/
void my_error(char *str)
{
    fprintf(stderr, "Error: %s\n", str);
    my_exit(84);
}
