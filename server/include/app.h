/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** app.h
*/

#ifndef APP_H_
    #define APP_H_

    #include <stdbool.h>
    #include "args.h"
    #include "serverdata.h"

    #define PROCESS_FAILURE 84
    #define PROCESS_SUCCESS 0

    #define MIN_PORT 1025
    #define MAX_PORT 65535
    #define MIN_MAP_SIZE 5
    #define MAX_MAP_SIZE 100
    #define MIN_CLIENTS 6
    #define MIN_FREQ 0
    #define MIN_NB_ARGS 12
    #define FIRST_CHAR 0
    #define NEXT_ARG 1
    #define FIRST_TEAM_NAME 0
    #define A_SECOND_TEAM 1
    #define BACK_TO_FLAG 1
    #define DEFAULT_FREQ 100

static const char ARG_PORT[] = "-p";
static const char ARG_DEBUG[] = "-d";
static const char ARG_WIDTH[] = "-x";
static const char ARG_HEIGHT[] = "-y";
static const char ARG_CLIENTS[] = "-c";
static const char ARG_FREQ[] = "-f";
static const char ARG_TNAME[] = "-n";

static const char *USAGE_MSG[] = {
    "./zappy_server -p <port> -x <width max 100> -y <height max 100> ",
    "-n <name1 name2 ...> -c <clientsNb> -f <freq> [-d]\n"
};

/*
Displays the program usage
*/
int display_usage(void);

/*
Fills ARGS depending on program arguments, given in AV
*/
void get_args(int ad, char *av[], arguments_t *args);

/*
Checks if every argument of ARGS is valid
*/
int check_args(arguments_t *args);

/*
Main loop of the ftp server, takes port as parameter
Returns EXIT_SUCCESS or EXIT_FAILURE
*/
int server(arguments_t *args);

#endif
