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

void my_error(char *str);
int ftp(int argc, char *argv[]);
void check_args(int argc, char *argv[]);
