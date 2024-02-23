/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** clientllist
*/

#pragma once

#include <stdlib.h>

typedef struct client_s {
    int fd;
    char *ip;
    char *username;
    char *password;
    int id;
    struct client_s *next;
} *client_t;

void add_client(client_t *clients, client_t new_client);
void remove_client(client_t *clients, int fd);
client_t create_client(int fd, char *ip, char *username, char *password);
