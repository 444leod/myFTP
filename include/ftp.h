/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** ftp
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "lib.h"
#include "clientllist.h"
#include "debug.h"
#include "garbage_collector.h"
#include "macros.h"

typedef struct server_info_s {
    int port;
    char *path;
    char *ip;
} *server_info_t;

int ftp(int argc, char *argv[]);
void check_args(int argc, char *argv[]);
int get_socket(void);
void bind_socket(int socketFd, int port, char **ip);
void listen_socket(int socketFd, int maxClients);
void accept_socket(int socketFd, void (*func)(int));
void reply_code(client_t client);
void print_fd_set(fd_set *set);
void loop_clients(client_t *clients, fd_set *readfds,
    fd_set *writefds, server_info_t server_info);
void handle_command(client_t client, fd_set *readfds,
    server_info_t server_info);
void get_port(int fd, int *port);
