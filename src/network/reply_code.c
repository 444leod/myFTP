/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** reply_code
*/

#include "ftp.h"
#include "fcntl.h"

const server_message_s serverMessages[] = {
    {SERVICE_READY,
        "Service ready in %d minutes."},
    {DATA_CONNECTION_ALREADY_OPEN,
        "Data connection already open; transfer starting."},
    {FILE_STATUS_OK,
        "File status okay; about to open data connection."},
    {COMMAND_OK,
        "Command okay."},
    {HELP_MESSAGE,
        "Help message."},
    {SERVICE_READY_NEW_USER,
        "Service ready for new user."},
    {SERVICE_CLOSING_CONTROL_CONNECTION,
        "Service closing control connection."},
    {CLOSING_DATA_CONNECTION,
        "Closing data connection."},
    {ENTERING_PASSIVE_MODE,
        "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."},
    {USER_LOGGED_IN,
        "User logged in, proceed."},
    {REQUESTED_FILE_ACTION_COMPLETED,
        "Requested file action okay, completed."},
    {PATHNAME_CREATED,
        "Pathname created."},
    {USERNAME_OK_NEED_PASSWORD,
        "Username okay, need password."},
    {NEED_ACCOUNT_FOR_LOGIN,
        "Need account for login."},
    {-1, NULL}
};

void display_message(int code, int socketFd)
{
    switch (code) {
    case SERVICE_READY:
        dprintf(socketFd, serverMessages[0].message, 0);
        return;
    case HELP_MESSAGE:
        dprintf(socketFd, serverMessages[4].message);
        return;
    default:
        break;
    }
    for (int i = 0; serverMessages[i].code != -1; i++) {
        if (serverMessages[i].code == code) {
            dprintf(socketFd, serverMessages[i].message);
            return;
        }
    }
}
