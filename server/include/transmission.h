/*
** EPITECH PROJECT, 2025
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
int receive_data(serverdata_t *sdata, fdarray_t *fdarray, client_t *client);

/*
Used to write client buffer output and send it to client
*/
int send_data(client_t *client, bool debug);

/*
Used to write DATA to client buffer output
*/
int set_message(client_t *client, char *cmd, char *data, bool debug);

/*
Used to find a player based on his id
*/
player_t *get_player_pos(serverdata_t *sdata, int player_id);

/*
Sends a message to all connected GUIs
*/
int send_guis(serverdata_t *sdata, fdarray_t *fdarray, char *cmd, char *data);

#endif
