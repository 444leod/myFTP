/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include <string.h>
#include "lib.h"

char **str_to_word_array(char *str, char *delim)
{
    char **array = malloc(sizeof(char *));
    int i = 0;
    char *start = str;
    char *end;

    end = strpbrk(start, delim);
    while (end != NULL) {
        array[i] = my_strndup(start, end - start);
        i++;
        array = realloc(array, sizeof(char *) * (i + 1));
        start = end + 1;
        end = strpbrk(start, delim);
    }
    array[i] = my_strdup(start);
    i++;
    array = realloc(array, sizeof(char *) * (i + 1));
    array[i] = NULL;
    return array;
}
