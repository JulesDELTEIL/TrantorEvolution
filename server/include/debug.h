/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** server.h
*/

#ifndef DEBUG_H_
    #define DEBUG_H_

    #include "structs.h"

void displayfds(fdarray_t *fdarray);

void debug_input(client_t *client, char *data, int size);
void debug_output(client_t *client, char *data, int size);

void debug_buffer(client_t *client);

#endif
