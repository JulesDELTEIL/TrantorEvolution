/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** first_cmd.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "debug.h"
#include "transmission.h"
#include "functions.h"

static void send_c_data_gui(serverdata_t *sdata, client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d", -1);
    send_data(client, data, NULL, sdata->debug);
    sprintf(data, "%d %d", sdata->args->width, sdata->args->height);
    send_data(client, data, NULL, sdata->debug);
}

static void send_c_data_ai(serverdata_t *sdata, client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d", client->player->team->space_left);
    send_data(client, data, NULL, sdata->debug);
    sprintf(data, "%d %d", sdata->args->width, sdata->args->height);
    send_data(client, data, NULL, sdata->debug);
}

static int send_players_infos(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    player_t *head = sdata->game_data.players;

    while (head != NULL) {
        send_pnw(sdata, head, client);
        head = head->next;
    }
}

int set_team(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strcmp(data, GRAPHIC_TEAM) == 0) {
        client->type = GUI;
        send_c_data_gui(sdata, client);
        send_players_infos(sdata, fdarray, client);
        return EXIT_SUCCESS;
    }
    for (uint_t k = 0; sdata->args->team_name[k] != NULL; k++) {
        if (strcmp(data, sdata->args->team_name[k]) == 0 &&
            new_player(sdata, fdarray, client, data) == EXIT_SUCCESS) {
            client->type = AI;
            send_c_data_ai(sdata, client);
            return EXIT_SUCCESS;
        }
    }
    send_data(client, "ko", NULL, sdata->debug);
    return EXIT_FAILURE;
}
