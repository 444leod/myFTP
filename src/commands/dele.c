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

/**
 * @brief Check if the given path is a file
 * @details Check if the given path is a file
 *
 * @param path the path to check
 *
 * @return true if the path is a file
*/
static bool is_file(char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

/**
 * @brief Check if the command is an error
 * @details Check if the command is an error
 * based on the client status and the length of the command
 *
 * @param client the client to check the command for
 * @param len the length of the command
 *
 * @return true if the command is an error
*/
static bool is_error(client_t client, int len)
{
    if (client->status == STATUS_NOT_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return true;
    }
    if (len != 2) {
        client->current_code = FILE_UNAVAILABLE;
        return true;
    }
    return false;
}

/**
 * @brief Check if the path is correct
 * @details Check if the path is correct
 * based on the server path
 *
 * @param path the path to check
 * @param server_path the server path
 *
 * @return true if the path is not correct
*/
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

/**
 * @brief Remove file
 * @details Remove file from the server
 *
 * @param client the client to execute the command for
 * @param server_info the server_info
 * @param filename the filename to remove
*/
static void remove_file(client_t client,
    server_info_t server_info, char *filename)
{
    char *path = NULL;

    if (filename[0] == '/')
        path = supercat(2, server_info->path, filename);
    else
        path = supercat(3, server_info->path, client->pwd, filename);
    if (is_path_not_correct(my_strdup(path), server_info->path)) {
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

/**
 * @brief Delete file
 * @details Delete file from the server
 * if the client is not logged in, the client will receive a not logged in
 *  error
 * if the path is not found, the client will receive a file unavailable error
 * if the path is found, the client will receive a requested file action
 * and the file will be deleted
 *
 * @param client the client to execute the command for
 * @param args the arguments of the command
 * @param server_info the server_info
*/
void dele(client_t client, char **args,
    UNUSED fd_set *readfds, server_info_t server_info)
{
    int len = tablen((void **)args);

    if (is_error(client, len))
        return;
    remove_file(client, server_info, args[1]);
}
