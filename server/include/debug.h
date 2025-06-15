/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** debug.h
*/

#ifndef DEBUG_H_
    #define DEBUG_H_

    #include "fdarray.h"

/*
Displays the current fdarray fds
*/
void displayfds(fdarray_t *fdarray);

/*
Displays input data and client fd source linked to the data
Only SIZE bytes will be displayed
*/
void debug_input(client_t *client, char *data, int size);

/*
Displays output data and client fd dest linked to the data
Only SIZE bytes will be displayed
*/
void debug_output(client_t *client, char *data, int size);

/*
Displays client command buffer
*/
void debug_buffer(client_t *client);

#endif
