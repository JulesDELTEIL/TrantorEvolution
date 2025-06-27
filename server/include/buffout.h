/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** buffout.h
*/

#include "macros.h"

#ifndef BUFFOUT_H_
    #define BUFFOUT_H_

typedef struct message_s message_t;

struct message_s {
    char *data;
    uint_t len;
    message_t *next;
};

#endif
