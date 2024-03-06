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
#include "garbage_collector.h"
#include "lib.h"
#include "clientllist.h"

typedef struct server_info_s {
    int port;
    char *path;
} *server_info_t;

int ftp(int argc, char *argv[]);
void check_args(int argc, char *argv[]);
int get_socket(void);
void bind_socket(int socketFd, int port);
void listen_socket(int socketFd, int maxClients);
void accept_socket(int socketFd, void (*func)(int));
void reply_code(int code, int socketFd);
void print_fd_set(fd_set *set);
void loop_clients(client_t *clients, fd_set *readfds, fd_set *writefds);
void handle_command(client_t client, fd_set *readfds);
