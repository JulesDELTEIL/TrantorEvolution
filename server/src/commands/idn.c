/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** idn.c
*/

#include <unistd.h>
#include <stdlib.h>

#include "structs.h"
#include "commands.h"

int cmd_idn(serverdata_t *sdata, client_t *client, uint cmd_idx)
{
    uint cmd_data_len = USER_COMMANDS[cmd_idx].datalen;
    uint8_t data[cmd_data_len];
    int rc = DEFAULTRC;

    rc = read(client->fd, data, cmd_data_len);
    if (rc < cmd_data_len)
        return EXIT_FAILURE;
    client->type = data[0];
    return EXIT_SUCCESS;
}