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
