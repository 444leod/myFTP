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

/**
 * @brief Wait for select
 * @details Wait for select to write on the client's socket
 *
 * @param clientFd the client file descriptor
 * @param client the client
 * @return int 0 if success, -1 if error
 */
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

/**
 * @brief Get the path from the arguments
 * @details Get the path from the arguments
 * based on the server path and the client pwd
 *
 * @param client the client to get the path from the arguments of
 * @param server_info the server_info
 * @return char* the path
 */
static char *get_path_from_args(client_t client, server_info_t server_info)
{
    char *path = NULL;

    if (client->args[1][0] == '/')
        path = supercat(2, server_info->path, client->args[1]);
    else
        path = supercat(3, server_info->path, client->pwd, client->args[1]);
    return path;
}

/**
 * @brief Retrieve a file
 * @details Retrieve a file from the server
 * and send it to the client
 *
 * @param client the client to retrieve the file from
 * @param server_info the server_info
 * @param clientFd the client file descriptor
 */
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
static bool is_correct_file(char *path)
{
    if (access(path, F_OK) == -1 || !is_file(path))
        return false;
    return true;
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
    return is_correct_file(path);
}

/**
 * @brief Check if the retr command has an error
 * @details Check if the retr command has an error
 *
 * @param client the client to check the retr command of
 * @param server_info the server_info
 * @param args the arguments of the retr command
 * @return true if error, false if not
*/
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
