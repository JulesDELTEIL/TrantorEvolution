/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** server.h
*/

#ifndef SERVERFUNCTIONS_H_
    #define SERVERFUNCTIONS_H_

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <sys/wait.h>
    #include <netinet/in.h>
    #include <poll.h>

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>

    #include "macros.h"
    #include "structs.h"

/*
Uses a port and returns a serverdata_t struct containing socket informations
Returns a serverdata_t struct
*/
serverdata_t setup_parameters(arguments_t *args);

/*
Sets the options described in the sdata struct into the socket
Returns EXIT_SUCCESS or EXIT_FAILURE
*/
int setup_server(serverdata_t *sdata);

/*
Main loop of the ftp server, takes port as parameter
Returns EXIT_SUCCESS or EXIT_FAILURE
*/
int server_loop(arguments_t *args);

/*
Function to call at end of ftp server, used to destroy entities
Returns EXIT_SUCCESS
*/
int close_server(serverdata_t *sdata, fdarray_t *fdarray);

/*
Setup the fdarray_t struct used to store all fds
Returns a fdarray_t
*/
fdarray_t setup_fds(int sockfd);

/*
Used to read data from client FD
Returns EXIT_SUCCESS or EXIT_FAILURE
*/
int input_fd(serverdata_t *sdata, client_t *client);

/*
Used to write data to client FD
Returns number of bytes written
*/
int send_data(client_t *client, const uint8_t *cmd, uint8_t *data, size_t datalen);

/*
Opens a connection with a client
*/
int openconnection(serverdata_t *sdata, fdarray_t *fdarray);

/*
Closes connection with a client
*/
int closeconnection(serverdata_t *sdata, client_t *client);

/*
Sets an empty client to use space later for an other one
*/
int setempty_client(client_t *client);

/*
Displays an error message MSG on the error output
Returns ERRORCODE
*/
int returnwitherror(const char *msg, int errorcode);

void debug_input(client_t *client, uint8_t *data, int size);
void debug_output(client_t *client, uint8_t *data, int size);

#endif
