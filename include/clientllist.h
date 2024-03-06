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
    int id;
    char *command;
    char *next_commands;
    char *username;
    int current_code;
    enum {
        STATUS_NOT_LOGGED_IN,
        STATUS_USERNAME_OK,
        STATUS_LOGGED_IN,
    } status;
    enum {
        NONE,
        PASSIVE,
        ACTIVE,
    } mode;
    enum {
        READING,
        WRITING,
        PROCESSING
    } data_status;
    struct client_s *next;
} *client_t;

void add_client(client_t new_client);
void remove_client(int fd);
client_t create_client(int fd, char *ip);
client_t *get_clients(void);
void clear_clients(void);
