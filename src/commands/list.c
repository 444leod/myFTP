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

static bool is_path_not_correct(char *path, char *server_path)
{
    char *folder = NULL;

    if (chdir(path) == -1) {
        chdir(server_path);
        return true;
    }
    folder = get_current_dir();
    if (strncmp(folder, server_path, strlen(server_path)) != 0) {
        chdir(server_path);
        return true;
    }
    chdir(server_path);
    return false;
}

bool is_list_error(client_t client, server_info_t server_info, char **args)
{
    char *path = NULL;
    char *arg = args[1] ? args[1] : "/.";

    if (arg[0] == '/')
        path = supercat(2, server_info->path, arg);
    else
        path = supercat(3, server_info->path, client->pwd, arg);
    if (is_path_not_correct(path, server_info->path)) {
        client->current_code = FILE_UNAVAILABLE;
        return true;
    }
    return false;
}
