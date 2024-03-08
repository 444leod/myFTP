/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** dele
*/

#include "ftp.h"
#include "reply_code.h"
#include <stdbool.h>
#include <sys/stat.h>

static bool is_file(char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

static bool is_error(client_t client, int len)
{
    if (client->status == STATUS_NOT_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return true;
    }
    if (len != 2) {
        client->current_code = SYNTAX_ERROR_IN_PARAMETERS;
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

static void remove_file(client_t client,
    server_info_t server_info, char *filename)
{
    char *path = NULL;

    if (filename[0] == '/')
        path = supercat(2, server_info->path, filename);
    else
        path = supercat(3, server_info->path, client->pwd, filename);
    if (is_path_not_correct(path, server_info->path)) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    if (access(path, F_OK) == -1 || !is_file(path)) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    if (remove(path) == 0)
        client->current_code = REQUESTED_FILE_ACTION_COMPLETED;
    else
        client->current_code = FILE_UNAVAILABLE;
}

void dele(client_t client, char **args,
    fd_set *readfds, server_info_t server_info)
{
    int len = tablen((void **)args);

    (void)readfds;
    if (is_error(client, len))
        return;
    remove_file(client, server_info, args[1]);
}
