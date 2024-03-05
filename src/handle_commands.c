/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_commands
*/

#include "clientllist.h"
#include <sys/select.h>
#include "commands.h"
#include "lib.h"
#include "ftp.h"
#include <unistd.h>
#include <stdio.h>

static void execute_command(char **command, client_t client, fd_set *readfds)
{
    size_t i = 0;
    for (; commands[i].command; i++) {
        if (strcmp(commands[i].command, command[0]) == 0) {
            commands[i].func(client, command, readfds);
            return;
        }
    }
    commands[i].func(client, command, readfds);
}

//TO DELETE!!!!!!!!!
typedef struct temp_s {
    char special_char;
    char *replace;
}temp_s;

//TO DELETE!!!!!!!!!
temp_s special_chars[] = {
    {'\r', "\\r"},
    {'\n', "\\n"},
    {'\t', "\\t"},
    {'\0', NULL}
};

static char *replace_special_chars(char *str)
{
    //TO DELETE!!!!!!!!!
    for (int i = 0; str[i]; i++) {
        for (int j = 0; special_chars[j].replace; j++) {
            if (str[i] == special_chars[j].special_char) {
                char *tmp = str + i + 1;
                char *tmp2 = str;
                tmp2[i] = '\0';
                str = supercat(3, tmp2, special_chars[j].replace, tmp);
                break;
            }
        }
    }
    return str;
}

void handle_command(client_t client, fd_set *readfds)
{
    printf("Command: %s\n", replace_special_chars(client->command));
    char *command = my_strdup(client->command);
    char **args = str_to_word_array(command, " \t");

    free(client->command);
    execute_command(args, client, readfds);
    client->data_status = WRITING;
}
