/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** args
*/

#ifndef ARGS_H_
    #define ARGS_H_

/*
struct arguments_t :
- int port
- int width (width of the map)
- int height (height of the map)
- int clientsnb (number of authorized clients per team)
- int freq (reciprocal of time unit)
- char **team_name (name of every team in an array, null terminated)
- bool debug
*/
typedef struct arguments_s {
    int port;
    int width;
    int height;
    int clientnb;
    int freq;
    char **team_name;
    bool debug;
} arguments_t;


#endif /* !ARGS_H_ */
