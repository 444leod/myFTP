/*
** EPITECH PROJECT, 2023
** garbage_collector
** File description:
** garbage_collector
*/

#include "garbage_collector.h"
#include "lib.h"

/**
 * @brief Malloc wrapper with garbage collector
 * @details Malloc wrapper with garbage collector, store malloced pointers in a
 * linked list
 *
 * @param size the size of the memory to allocate
 *
 * @return void* the pointer to the allocated memory
*/
void *my_malloc(size_t size)
{
    void *variable = malloc(size);
    g_llist_t *llist = get_llist();

    if (variable == NULL)
        my_error("Malloc failed");
    *llist = g_insert_end(variable, *llist);
    if (*llist == NULL)
        my_error("Malloc failed");
    return variable;
}

/**
 * @brief Free wrapper with garbage collector
 * @details Free wrapper with garbage collector, free the pointer and remove it
 * from the linked list
 *
 * @param pointer the pointer to free
*/
void my_free(void *pointer)
{
    g_llist_t *llist = get_llist();
    g_llist_t temp;

    if ((*llist)->data == pointer) {
        *llist = g_delete_begin(*llist);
        return;
    }
    temp = (*llist)->next;
    while (temp != *llist) {
        if (temp->data == pointer) {
            temp = g_delete_begin(temp);
            return;
        }
        temp = temp->next;
    }
    free(pointer);
}

/**
 * @brief Free all the pointers in the linked list
*/
void my_free_all(void)
{
    g_llist_t *llist = get_llist();

    while (*llist)
        *llist = g_delete_begin(*llist);
}

/**
 * @brief Malloc wrapper (no garbage collector)
 * @details Malloc wrapper (no garbage collector), if malloc failed, exit the
 * program
 *
 * @param size the size of the memory to allocate
 *
 * @return void* the pointer to the allocated memory
*/
void *force_malloc(size_t size)
{
    void *variable = malloc(size);

    if (variable == NULL)
        my_error("Malloc failed");
    return variable;
}

/**
 * @brief Free wrapper (no garbage collector)
 *
 * @param pointer the pointer to free
*/
void force_free(void *pointer)
{
    free(pointer);
}
