/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** stor
*/

#include "ftp.h"
#include "reply_code.h"
#include <stdbool.h>
#include <sys/stat.h>

static int wait_for_select(int clientFd, client_t client)
{
    fd_set readfds;
    int ret;

    FD_ZERO(&readfds);
    FD_SET(clientFd, &readfds);
    ret = select(clientFd + 1, &readfds, NULL, NULL, NULL);
    if (ret == -1) {
        client->current_code = FILE_UNAVAILABLE;
        reply_code(client);
        return -1;
    }
    return 0;
}

static char *get_path_from_args(client_t client, server_info_t server_info)
{
    char *path = NULL;

    if (client->args[1][0] == '/')
        path = supercat(2, server_info->path, client->args[1]);
    else
        path = supercat(3, server_info->path, client->pwd, client->args[1]);
    return path;
}

void stor(client_t client, server_info_t server_info, int clientFd)
{
    char *path = get_path_from_args(client, server_info);
    FILE* file = fopen(path, "wb");
    char buffer[1024];
    size_t bytesRead = 1;

    if (!file) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    while (bytesRead > 0) {
        if (wait_for_select(clientFd, client) == -1)
            return;
        bytesRead = read(clientFd, buffer, 1024);
        fwrite(buffer, 1, bytesRead, file);
    }
    fclose(file);
    client->current_code = FILE_STATUS_OK;
    reply_code(client);
}

static bool is_valid_file(server_info_t server_info,
    client_t client, char *arg)
{
    char *path = NULL;
    FILE *file = NULL;

    if (arg[0] == '/')
        path = supercat(2, server_info->path, arg);
    else
        path = supercat(3, server_info->path, client->pwd, arg);
    file = fopen(path, "wb");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

static bool is_path_not_correct(char *path, char *server_path)
{
    char *folder = NULL;

    for (int i = strlen(path); i >= 0; i--) {
        if (path[i] == '/') {
            path[i] = '\0';
            break;
        }
    }
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

bool is_stor_error(client_t client, server_info_t server_info, char **args)
{
    char *path = NULL;
    char *arg = args[1];

    if (arg == NULL) {
        client->current_code = FILE_UNAVAILABLE;
        return true;
    }
    if (arg[0] == '/')
        path = supercat(2, server_info->path, arg);
    else
        path = supercat(3, server_info->path, client->pwd, arg);
    if (is_path_not_correct(path, server_info->path) ||
            !is_valid_file(server_info, client, arg)) {
        client->current_code = FILE_UNAVAILABLE;
        return true;
    }
    return false;
}
