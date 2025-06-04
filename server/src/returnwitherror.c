/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** errors.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int returnwitherror(const char *msg, int errorcode)
{
    size_t len = strlen(msg);

    write(2, msg, len);
    return errorcode;
}
