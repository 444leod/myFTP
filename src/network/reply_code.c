/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** reply_code
*/

#include "fcntl.h"
#include <stdio.h>
#include "reply_code.h"

const server_message_s serverMessages[] = {
    {SERVICE_READY,
        "%d Service ready in %d minutes.\n"},
    {DATA_CONNECTION_ALREADY_OPEN,
        "%d Data connection already open; transfer starting.\n"},
    {FILE_STATUS_OK,
        "%d File status okay; about to open data connection.\n"},
    {COMMAND_OK,
        "%d Command okay.\n"},
    {HELP_MESSAGE,
        "%d Help message.\n"},
    {SERVICE_READY_NEW_USER,
        "%d Service ready for new user.\n"},
    {SERVICE_CLOSING_CONTROL_CONNECTION,
        "%d Service closing control connection.\n"},
    {CLOSING_DATA_CONNECTION,
        "%d Closing data connection.\n"},
    {ENTERING_PASSIVE_MODE,
        "%d Entering Passive Mode (h1,h2,h3,h4,p1,p2).\n"},
    {USER_LOGGED_IN,
        "%d User logged in, proceed.\n"},
    {REQUESTED_FILE_ACTION_COMPLETED,
        "%d Requested file action okay, completed.\n"},
    {PATHNAME_CREATED,
        "%d Pathname created.\n"},
    {USERNAME_OK_NEED_PASSWORD,
        "%d Username okay, need password.\n"},
    {NEED_ACCOUNT_FOR_LOGIN,
        "%d Need account for login.\n"},
    {SYNTAX_ERROR,
        "%d Syntax error, command unrecognized.\n"},
    {SYNTAX_ERROR_IN_PARAMETERS,
        "%d Syntax error in parameters or arguments.\n"},
    {COMMAND_NOT_IMPLEMENTED,
        "%d Command not implemented.\n"},
    {BAD_COMMAND_SEQUENCE,
        "%d Bad sequence of commands.\n"},
    {COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER,
        "%d Command not implemented for that parameter.\n"},
    {NOT_LOGGED_IN,
        "%d Not logged in.\n"},
    {NEED_ACCOUNT_FOR_STORING_FILES,
        "%d Need account for storing files.\n"},
    {FILE_UNAVAILABLE,
        "%d File unavailable (e.g., file not found, no access).\n"},
    {PAGE_TYPE_UNKNOWN,
        "%d Page type unknown.\n"},
    {EXCEEDED_STORAGE_ALLOCATION,
        "%d Exceeded storage allocation (for current directory or dataset).\n"},
    {BAD_FILENAME,
        "%d Bad filename.\n"},
    {-1, (void *)0}
};

void reply_code(int code, int socketFd)
{
    switch (code) {
        case SERVICE_READY:
            dprintf(socketFd, serverMessages[0].message, code, 0);
            return;
        case HELP_MESSAGE:
            dprintf(socketFd, serverMessages[4].message, code);
            return;
        default:
            break;
    }
    for (int i = 0; serverMessages[i].code != -1; i++) {
        if (serverMessages[i].code == code) {
            dprintf(socketFd, serverMessages[i].message, code);
            return;
        }
    }
}
