/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** recv
*/

#include "ftp.h"
#include "reply_code.h"
#include <stdbool.h>
#include <sys/stat.h>

static int wait_for_select(int clientFd, client_t client)
{
    fd_set writefds;
    int ret;

    FD_ZERO(&writefds);
    FD_SET(clientFd, &writefds);
    ret = select(clientFd + 1, NULL, &writefds, NULL, NULL);
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

void retr(client_t client, server_info_t server_info, int clientFd)
{
    char *path = get_path_from_args(client, server_info);
    FILE* file = fopen(path, "rb");
    char buffer[1024];
    size_t bytesRead = 1;

    if (!file) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    while (bytesRead > 0) {
        bytesRead = fread(buffer, 1, 1024, file);
        if (wait_for_select(clientFd, client) == -1)
            return;
        write(clientFd, buffer, bytesRead);
    }
    fclose(file);
    client->current_code = FILE_STATUS_OK;
    reply_code(client);
}

static bool is_file(char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

static bool is_correct_file(char *path)
{
    if (access(path, F_OK) == -1 || !is_file(path))
        return false;
    return true;
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
    return is_correct_file(path);
}

bool is_retr_error(client_t client, server_info_t server_info, char **args)
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
    if (is_path_not_correct(path, server_info->path)) {
        client->current_code = FILE_UNAVAILABLE;
        return true;
    }
    return false;
}
