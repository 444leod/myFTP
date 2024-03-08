/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** clientllist
*/

#pragma once

#include <stdlib.h>

typedef struct external_socket_s {
    int fd;
    char *ip;
    char *command;
    int port;
    int pid;
    enum {
        NO_MODE,
        PASSIVE,
        ACTIVE,
    } mode;
} *external_socket_t;

typedef struct client_s {
    int fd;
    char *ip;
    int id;
    char *command;
    char *next_commands;
    char *username;
    int current_code;
    char *pwd;
    char *buffer;
    char **args;
    external_socket_t external_socket;
    enum {
        STATUS_NOT_LOGGED_IN,
        STATUS_USERNAME_OK,
        STATUS_LOGGED_IN,
    } status;
    enum {
        READING,
        WRITING,
        PROCESSING,
        WAITING_FOR_FORK
    } data_status;
    struct client_s *next;
} *client_t;

void add_client(client_t new_client);
void remove_client(int fd);
client_t create_client(int fd, char *ip);
client_t *get_clients(void);
void clear_clients(void);
external_socket_t create_external_socket(void);
