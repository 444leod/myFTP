/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** replace_char
*/

char *replace_char(char *str, char find, char replace)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == find) {
            str[i] = replace;
        }
    }
    return str;
}
