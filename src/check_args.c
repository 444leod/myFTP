/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** check_args
*/

#include "ftp.h"

static void check_args_number(int argc)
{
    if (argc != 3) {
        printf("Usage: ./myftp port path\n");
        exit(84);
    }
}

static void check_port(char *port)
{
    for (int i = 0; port[i]; i++)
        if (port[i] < '0' || port[i] > '9')
            my_error("Invalid port");
}

static void check_path(char *path)
{
    if (chdir(path) == -1)
        my_error("Invalid path");
}

void check_args(int argc, char *argv[])
{
    check_args_number(argc);
    check_port(argv[1]);
    check_path(argv[2]);
}
