/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** accounts
*/

#pragma once

typedef struct accounts_s {
    char *username;
    char *password;
} accounts_s;

const accounts_s accounts[] = {
    {"Anonymous", ""},
    {NULL, NULL}
};
