/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** get_clients
*/

#include "clientllist.h"

/**
 * @brief Get the clients
 * @details Get the clients linked list
*/
client_t *get_clients(void)
{
    static client_t clients = NULL;

    return &clients;
}
