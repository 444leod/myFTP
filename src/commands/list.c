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

/**
 * @brief Wait for select
 * @details Wait for select to write
 *
 * @param clientFd the client file descriptor
 * @param client the client to wait for select
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
 * @brief Get the ls result
 * @details Get the ls result of the client
 *
 * @param server_info the server_info
 * @param client the client to get the ls result of
 * @return FILE* the file to get the ls result
 */
FILE *get_ls_result(server_info_t server_info, client_t client)
{
    char *path = tablen((void **)client->args) == 2 ? client->args[1] : "/.";
    char *cmd = NULL;
    FILE *ls = NULL;

    cmd = supercat(4, "ls -l ", server_info->path, client->pwd, path);
    ls = popen(cmd, "r");
    return ls;
}

/**
 * @brief Close the file and the client
 * @details Close the file and the client
 *
 * @param ls the file to close
 * @param clientFd the client file descriptor
 * @param client the client to close
 */
static void close_all(FILE *ls, int clientFd, client_t client)
{
    pclose(ls);
    close(clientFd);
    client->current_code = FILE_STATUS_OK;
    reply_code(client);
}

/**
 * @brief List the directory
 * @details List the directory of the client
 * if the status is not logged in, the client will receive a not logged in
 * error
 * if the path is not found, the client will receive a file unavailable error
 * if the path is found, the client will receive a requested file action
 *
 * @param client the client to execute the command for
 * @param server_info the server_info
 */
void list(client_t client, server_info_t server_info, int clientFd)
{
    FILE *ls = get_ls_result(server_info, client);
    char buffer[1024] = {0};

    if (ls == NULL) {
        client->current_code = FILE_UNAVAILABLE;
        reply_code(client);
        return;
    }
    while (fgets(buffer, 1024, ls) != NULL) {
        if (wait_for_select(clientFd, client) == -1)
            return;
        write(clientFd, buffer, strlen(buffer));
    }
    close_all(ls, clientFd, client);
}

/**
 * @brief Check if the list command has an error
 * @details Check if the list command has an error
 *
 * @param client the client to check the list command of
 * @param server_info the server_info
 * @param args the arguments of the list command
 * @return true if error, false if not
 */
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

/**
 * @brief Check if the list command has an error
 * @details Check if the list command has an error
 *
 * @param client the client to check the list command of
 * @param server_info the server_info
 * @param args the arguments of the list command
 * @return true if error, false if not
 */
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
