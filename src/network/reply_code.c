/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** reply_code
*/

#include "ftp.h"

void display_message(int code, int socketFd)
{
    switch (code) {
    case SERVICE_READY:
        fprintf(socketFd, serverMessages[0].message, 0);
        return;
    case HELP_MESSAGE:
        fprintf(socketFd, serverMessages[4].message);
        return;
    default:
        break;
    }
    for (int i = 0; serverMessages[i].code != -1; i++) {
        if (serverMessages[i].code == code) {
            fprintf(socketFd, serverMessages[i].message);
            return;
        }
    }
}
