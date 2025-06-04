/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-jetpack-baptiste.dunes
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "structs.h"

typedef int (*handler_t)(serverdata_t *sdata, client_t *client, void *data);

typedef struct command_s {
    uint8_t code;
    int (*handler_t)(serverdata_t *sdata, client_t *client, void *data);
} command_t;


int process_handler(serverdata_t *sdata, client_t *client, uint8_t code);

static const command_t user_commands[] = {
};

static const int NB_COMMANDS = sizeof(user_commands) / sizeof(command_t);

#endif
