/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "garbage_collector.h"

static size_t count_words(char *str, char *delim)
{
    size_t count = 0;
    char *start = str;
    char *end;

    end = strpbrk(start, delim);
    while (end != NULL) {
        count++;
        start = end + 1;
        end = strpbrk(start, delim);
    }
    count++;
    return count;
}

char **str_to_word_array(char *str, char *delim)
{
    char **array = my_malloc(sizeof(char *) * (count_words(str, delim) + 1));
    int i = 0;
    char *start = str;
    char *end;

    end = strpbrk(start, delim);
    while (end != NULL) {
        array[i] = my_strndup(start, end - start);
        i++;
        start = end + 1;
        end = strpbrk(start, delim);
    }
    array[i] = my_strdup(start);
    i++;
    array[i] = NULL;
    return array;
}
