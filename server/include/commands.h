/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-jetpack-baptiste.dunes
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "structs.h"

int buffer_handler(serverdata_t *sdata, client_t *client);

typedef int (*handler_t)(serverdata_t *sdata, client_t *client);

typedef struct command_s {
    char *command;
    int (*handler)(serverdata_t *sdata, client_t *client, char *data);
} command_t;

int cmd_tna(serverdata_t *sdata, client_t *client, char *data);
int cmd_idn(serverdata_t *sdata, client_t *client, char *data);

static const command_t USER_COMMANDS[] = {
    {"tna", &cmd_tna},
    {"idn", &cmd_idn},
};

static const int NB_USER_COMMANDS = sizeof(USER_COMMANDS) / sizeof(command_t);

#endif
