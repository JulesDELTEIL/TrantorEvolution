/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** transmission.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "functions.h"
#include "debug.h"
#include "transmission.h"

static int add_circular(client_t *client, char *buffer)
{
    char *newbuff = NULL;
    uint_t c_bufflen = 0;
    uint_t n_bufflen = strlen(buffer);

    if (client->buffin != NULL)
        c_bufflen = strlen(client->buffin);
    newbuff = malloc(sizeof(char) * (c_bufflen + n_bufflen + 1));
    for (uint_t k = 0; k < c_bufflen; k++)
        newbuff[k] = client->buffin[k];
    for (uint_t k = 0; k < n_bufflen; k++)
        newbuff[k + c_bufflen] = buffer[k];
    newbuff[c_bufflen + n_bufflen] = 0;
    if (client->buffin != NULL)
        free(client->buffin);
    client->buffin = newbuff;
    client->buffin_addition = true;
    return EXIT_SUCCESS;
}

int receive_data(serverdata_t *sdata, fdarray_t *fdarray, client_t *client)
{
    char buffer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    rc = read(client->fd, buffer, BUFFSIZE - 1);
    if (rc == 0) {
        if (sdata->debug)
            printf("Cfd%-3d ↓  ✕\n", client->fd);
        return closeconnection(sdata, fdarray, client);
    } else if (rc == -1)
        return EXIT_FAILURE;
    if (sdata->debug)
        debug_input(client, buffer, rc);
    if (rc < 2)
        return EXIT_FAILURE;
    add_circular(client, buffer);
    return EXIT_SUCCESS;
}

static int get_datalen(char *data)
{
    if (data == NULL)
        return 0;
    return strlen(data);
}

static int delete_last_message(message_t *prev)
{
    if (prev == NULL)
        return EXIT_FAILURE;
    free(prev->next->data);
    free(prev->next);
    return EXIT_SUCCESS;
}

int send_data(client_t *client, bool debug)
{
    message_t *msg = client->buffout;
    message_t *prev = client->buffout;

    while (msg->next != NULL) {
        prev = msg;
        msg = msg->next;
    }
    write(client->fd, msg->data, msg->len - 1);
    if (debug)
        debug_output(client, msg->data, msg->len - 1);
    free(msg->data);
    free(msg);
    if (msg == client->buffout) {
        client->buffout = NULL;
    } else {
        prev->next = NULL;
    }
}

static int add_message_to_queue(client_t *client, char *msg, uint_t len)
{
    message_t *new = malloc(sizeof(message_t));

    new->len = len;
    new->data = strdup(msg);
    pthread_mutex_lock(&(client->buffout_mutex));
    new->next = client->buffout;
    client->buffout = new;
    pthread_mutex_unlock(&(client->buffout_mutex));
}

int set_message(client_t *client, char *cmd, char *data)
{
    uint_t datalen = get_datalen(data);
    uint_t cmdlen = get_datalen(cmd);
    uint_t spacelen = (uint_t) (datalen > 0);
    uint_t packetlen = cmdlen + spacelen + datalen + 1 + 1;
    char fullpacket[packetlen];

    if (cmd == NULL)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < cmdlen; k++)
        fullpacket[k] = cmd[k];
    if (spacelen > 0)
        fullpacket[cmdlen] = ' ';
    for (size_t k = 0; k < datalen; k++)
        fullpacket[cmdlen + spacelen + k] = data[k];
    fullpacket[cmdlen + spacelen + datalen] = '\n';
    fullpacket[cmdlen + spacelen + datalen + 1] = '\0';
    return add_message_to_queue(client, fullpacket, packetlen);
}
