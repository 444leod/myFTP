/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** garbage_collector
*/

#include "lib.h"
#include "garbage_collector.h"

static garbage_node_t *get_garbage(void)
{
    static garbage_node_t list = NULL;

    return &list;
}

static void add_to_garbage_collector(void *ptr)
{
    garbage_node_t *list = get_garbage();
    garbage_node_t new_node = malloc(sizeof(struct garbage_node_s));

    if (!new_node)
        my_exit(84);
    new_node->ptr = ptr;
    new_node->next = NULL;
    if (!*list) {
        *list = new_node;
        return;
    }
    while ((*list)->next)
        *list = (*list)->next;
    (*list)->next = new_node;
}

void my_free(void *ptr)
{
    garbage_node_t *list = get_garbage();
    garbage_node_t tmp = *list;
    garbage_node_t prev = NULL;

    while (tmp) {
        if (tmp->ptr != ptr) {
            prev = tmp;
            tmp = tmp->next;
            continue;
        }
        if (prev)
            prev->next = tmp->next;
        else
            *list = tmp->next;
        free(tmp->ptr);
        free(tmp);
        return;
    }
}

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
        my_exit(84);
    add_to_garbage_collector(ptr);
    return ptr;
}

void clear_garbage_collector(void)
{
    garbage_node_t *list = get_garbage();
    garbage_node_t tmp = *list;

    while (*list) {
        tmp = *list;
        *list = (*list)->next;
        if (tmp->ptr)
            free(tmp->ptr);
    }
}
