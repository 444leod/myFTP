/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** cwd
*/

#include "ftp.h"
#include "clientllist.h"
#include "reply_code.h"
#include "lib.h"
#include <sys/select.h>

/**
 * @brief Verify the path
 * @details Verify the path of the client based on the server path
 *
 * @param client the client to verify the path of
 * @param server_path the server path
*/
static void verify_path(client_t client, char *server_path)
{
    char *new_path = get_current_dir();

    if (new_path == NULL) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    if (strncmp(new_path, server_path, strlen(server_path)) != 0){
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    client->current_code = REQUESTED_FILE_ACTION_COMPLETED;
    client->pwd = supercat(2, new_path + strlen(server_path), "/");
}

/**
 * @brief Change the working directory
 * @details Change the working directory of the client
 * if the status is not logged in, the client will receive a not logged in
 * error
 * if the path is not found, the client will receive a file unavailable error
 * if the path is found, the client will receive a requested file action
 *
 * @param client the client to execute the command for
 * @param path the path to change to
 * @param server_info the server_info
*/
static void change_working_directory(client_t client, char *path,
    server_info_t server_info)
{
    char *new_path = NULL;

    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    if (strlen(path) == 0) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    if (path[0] == '/')
        new_path = supercat(2, server_info->path, path);
    else
        new_path = supercat(3, server_info->path, client->pwd, path);
    if (chdir(new_path) == -1) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    verify_path(client, server_info->path);
}

/**
 * @brief Change the working directory
 * @details Change the working directory of the client
 *
 * @param client the client to execute the command for
 * @param args the arguments of the command
 * @param server_info the server_info
*/
void cwd(client_t client, char **args,
    UNUSED fd_set *readfds, server_info_t server_info)
{
    int len = tablen((void **)args);

    switch (len) {
        case 2:
            change_working_directory(client, args[1], server_info);
            break;
        default:
            client->current_code = FILE_UNAVAILABLE;
            break;
    }
    chdir(server_info->path);
}
