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

extern const accounts_s accounts[];
