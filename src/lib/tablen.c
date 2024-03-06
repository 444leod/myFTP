/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** tablen
*/

int tablen(void **tab)
{
    int i = 0;

    while (tab[i] != (void *)0)
        i++;
    return i;
}
