/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** dlist
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include "accounts.h"
#include "lib.h"
#include <sys/select.h>
#include <stdbool.h>

FILE *get_ls_result(server_info_t server_info, client_t client)
{
    char *path = tablen((void **)client->args) == 2 ? client->args[1] : "/.";
    char *cmd = NULL;
    FILE *ls = NULL;

    cmd = supercat(4, "ls -l ", server_info->path, client->pwd, path);
    ls = popen(cmd, "r");
    return ls;
}

static void close_all(FILE *ls, int clientFd, client_t client)
{
    pclose(ls);
    close(clientFd);
    client->current_code = FILE_STATUS_OK;
    reply_code(client);
}

void list(client_t client, server_info_t server_info, int clientFd)
{
    FILE *ls = get_ls_result(server_info, client);
    char buffer[1024] = {0};
    fd_set writefds;

    if (ls == NULL) {
        client->current_code = FILE_UNAVAILABLE;
        reply_code(client);
        return;
    }
    while (fgets(buffer, 1024, ls) != NULL) {
        FD_ZERO(&writefds);
        FD_SET(clientFd, &writefds);
        if (select(clientFd + 1, NULL, &writefds, NULL, NULL) == -1) {
            client->current_code = CANT_OPEN_DATA_CONNECTION;
            reply_code(client);
            return;
        }
        write(clientFd, buffer, strlen(buffer));
    }
    close_all(ls, clientFd, client);
}
