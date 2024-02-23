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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>

typedef struct server_info_s {
    int port;
    char *path;
} *server_info_t;

enum REPLY_CODES {
    SERVICE_READY = 120,
    DATA_CONNECTION_ALREADY_OPEN = 125,
    FILE_STATUS_OK = 150,
    COMMAND_OK = 200,
    HELP_MESSAGE = 214,
    SERVICE_READY_NEW_USER = 220,
    SERVICE_CLOSING_CONTROL_CONNECTION = 221,
    CLOSING_DATA_CONNECTION = 226,
    ENTERING_PASSIVE_MODE = 227,
    USER_LOGGED_IN = 230,
    REQUESTED_FILE_ACTION_COMPLETED = 250,
    PATHNAME_CREATED = 257,
    USERNAME_OK_NEED_PASSWORD = 331,
    NEED_ACCOUNT_FOR_LOGIN = 332,
};

typedef struct server_message_s {
    int code;
    char *message;
} server_message_s;

void my_error(char *str);
int ftp(int argc, char *argv[]);
void check_args(int argc, char *argv[]);
int get_socket(void);
void bind_socket(int socketFd, int port);
void listen_socket(int socketFd, int maxClients);
void accept_socket(int socketFd, void (*func)(int));
void reply_code(int code, int socketFd);
void prepare_exit(int socketFd);
void my_exit(int status);
