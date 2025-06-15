/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** transmission.h
*/

#include "serverdata.h"
#include "fdarray.h"

#ifndef TRANSMISSION_H_
    #define TRANSMISSION_H_

/*
Used to read data from client FD
Returns EXIT_SUCCESS or EXIT_FAILURE
*/
int receive_data(serverdata_t *sdata, client_t *client);

/*
Used to write data to client FD
Returns number of bytes written
*/
int send_data(client_t *client, char *cmd, char *data, bool debug);

#endif
