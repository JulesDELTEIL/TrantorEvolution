/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** transmission.h
*/

#include "serverdata.h"
#include "fdarray.h"

#ifndef TRANSMISSION_H_
    #define TRANSMISSION_H_

static const char M_OK[] = "ok";
static const char M_KO[] = "ko";
static const char M_DEAD[] = "dead";
static const char M_INC_START[] = "Elevation underway";
static const char M_INC_END[] = "Current level: ";
static const char M_BDC_MSG[] = "message";

static const char M_MSZ[] = "msz";
static const char M_BCT[] = "bct";
static const char M_BIO[] = "bio";
static const char M_TNA[] = "tna";
static const char M_PNW[] = "pnw";
static const char M_PPO[] = "ppo";
static const char M_PLV[] = "plv";
static const char M_PIN[] = "pin";
static const char M_PEX[] = "pex";
static const char M_PBC[] = "pbc";
static const char M_PIC[] = "pic";
static const char M_PIE[] = "pie";
static const char M_PFK[] = "pfk";
static const char M_PDR[] = "pdr";
static const char M_PGT[] = "pgt";
static const char M_PDI[] = "pdi";
static const char M_ENW[] = "enw";
static const char M_EBO[] = "ebo";
static const char M_EDI[] = "edi";
static const char M_SGT[] = "sgt";
static const char M_SST[] = "sst";
static const char M_SEG[] = "seg";
static const char M_SMG[] = "smg";
static const char M_SUC[] = "suc";
static const char M_SBP[] = "sbp";

/*
Used to read data from client FD
Returns EXIT_SUCCESS or EXIT_FAILURE
*/
int receive_data(serverdata_t *sdata, fdarray_t *fdarray, client_t *client);

/*
Used to write client buffer output and send it to client
*/
int send_data(client_t *client, bool debug);

/*
Used to write DATA to client buffer output
*/
int set_message(client_t *client, const char *cmd, char *data);

/*
Used to find a player based on his id
*/
player_t *get_player_pos(serverdata_t *sdata, int player_id);

/*
Sends a message to all connected GUIs
*/
int send_guis(serverdata_t *sdata, fdarray_t *fdarray, const char *cmd,
    char *data);

#endif
