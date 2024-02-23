/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** garbage_collector
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct garbage_node_s {
    void *ptr;
    struct garbage_node_s *next;
} *garbage_node_t;

void *my_malloc(size_t size);
void my_free(void *ptr);
void clear_garbage_collector(void);
