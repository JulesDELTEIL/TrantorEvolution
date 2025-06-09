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
    send_data(client, WRC, NULL, 0);
}

int find_command(serverdata_t *sdata, client_t *client, uint8_t *command, uint8_t *data)
{
    for (uint k = 0; k < NB_COMMANDS; k++) {
        if (user_commands[k].command[0] == command[0] &&
            user_commands[k].command[1] == command[1] &&
            user_commands[k].command[2] == command[2])
            return user_commands[k].handler(sdata, client, data);
    }
    handle_unrecognized_code(sdata, client, NULL);
    return EXIT_FAILURE;
}

static bool check_packet_conform(client_t *client)
{
    if (client->buffsize < 8)
        return false;
    for (uint k = 0; k < PREAMBLE_LEN; k++)
        if (client->buffer[k] != 0) {
            return false;
        }
    return true;
}

static void delete_command(client_t *client, uint datasize)
{
    uint to_delete = PREAMBLE_LEN + SIZEINFO_LEN + datasize;
    int remaining = client->buffsize - to_delete;
    uint8_t copy[remaining];

    for (uint k = 0; k < remaining; k++)
        copy[k] = client->buffer[k + to_delete];
    for (uint k = 0; k < client->buffsize; k++)
        client->buffer[k] = 0;
    for (uint k = 0; k < remaining; k++)
        client->buffer[k] = copy[k];
    client->buffsize -= to_delete;
}

static int extract_data(client_t *client, uint8_t *cmd_buf, uint8_t *data_buf)
{
    uint datasize = 0;

    if (check_packet_conform(client) == false)
        return -1;
    datasize = client->buffer[SIZEINFO_BEGIN_IDX];
    if ((PREAMBLE_LEN + SIZEINFO_LEN + datasize) > client->buffsize)
        return 0;
    for (uint k = 0; k < CMD_LEN; k++)
        cmd_buf[k] = client->buffer[k + CMD_BEGIN_IDX];
    for (uint k = 0; k < datasize; k++)
        data_buf[k] = client->buffer[k + DATA_BEGIN_IDX];
    delete_command(client, datasize);
    return datasize;
}

int command_handler(serverdata_t *sdata, client_t *client)
{
    uint8_t command[3] = {0};
    uint8_t data[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    rc = extract_data(client, command, data);
    if (rc <= 0)
        return EXIT_FAILURE;
    return find_command(sdata, client, command, data);
}
