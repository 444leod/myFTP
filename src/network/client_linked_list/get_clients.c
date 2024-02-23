/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** get_clients
*/

#include "clientllist.h"

client_t *get_clients(void)
{
    static client_t clients = NULL;

    return &clients;
}
