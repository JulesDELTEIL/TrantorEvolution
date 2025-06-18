/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** end.c
*/

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "serverdata.h"
#include "fdarray.h"

int destroy_client(client_t *client)
{
    if (client == NULL)
        return EXIT_FAILURE;
    if (client->buffer != NULL)
        free(client->buffer);
    return EXIT_SUCCESS;
}

void destroy_args(arguments_t *args)
{
    if (!args->team_name)
        return;
    for (int i = 0; args->team_name[i] != NULL; i++)
        free(args->team_name[i]);
    free(args->team_name);
}

void destroy_map(map_t **map)
{
    if (!map)
        return;
    for (int i = 0; map[i] != NULL; i++)
        free(map[i]);
    free(map);
}

void destroy_teams(team_t *teams, int team_count)
{
    if (!teams)
        return;
    for (int i = 0; i < team_count; i++) {
        free(teams[i].name);
    }
    free(teams);
}

static void destroy_players(player_t *head)
{
    player_t *temp = NULL;

    while (head != NULL) {
        free(head->team);
        temp = head->next;
        free(head);
        head = temp;
    }
}

int close_server(serverdata_t *sdata, fdarray_t *fdarray, pthread_t *mapthr)
{
    close(sdata->sockfd);
    sdata->is_running = false;
    pthread_join(*mapthr, NULL);
    for (size_t k = 0; k < NBTOTAL_FD; k++) {
        destroy_client(&(fdarray->clients[k]));
    }
    destroy_args(sdata->args);
    destroy_map(sdata->game_data.trantor_map);
    destroy_teams(sdata->game_data.teams, sdata->game_data.nb_of_teams);
    destroy_players(sdata->game_data.players);
    return EXIT_SUCCESS;
}
