/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-jetpack-baptiste.dunes
** File description:
** commands.c
*/

#include <stdio.h>
#include <unistd.h>

#include "commands.h"
#include "functions.h"

static void handle_unrecognized_code(serverdata_t *sdata, client_t *client,
    void *db)
{
    uint8_t data[1024];
    uint8_t code = 4;

    read(client->fd, data, 1024);
    output_fd(client, 4, NULL, 0);
    memcpy(data, &code, 1);
    debug_output(data, 1);
}

static handler_t get_handler(uint8_t code)
{
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (user_commands[i].code == code)
            return user_commands[i].handler_t;
    }
    return NULL;
}

int process_handler(serverdata_t *sdata, client_t *client, uint8_t code)
{
    handler_t handler = get_handler(code);

    if (handler != NULL) {
        return handler(sdata, client, NULL);
    } else {
        handle_unrecognized_code(sdata, client, NULL);
        return EXIT_FAILURE;
    }
}
