/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** events.hpp
*/

#ifndef NET_EVENTS_HPP_
    #define NET_EVENTS_HPP_

    #include <queue>
    #include <map>
    #include <functional>

enum NetEvent_e {
    NET_MSIZE = 0,
    NET_TILE,
    NET_MAP,
    NET_TEAMS,
    NET_NEW,
    NET_PPOS,
    NET_PLVL,
    NET_PINV,
    NET_PUSH,
    NET_CAST,
    NET_PINC,
    NET_PEGG,
    NET_PDROP,
    NET_PGET,
    NET_PDEAD,
    NET_ELAID,
    NET_ENEW,
    NET_EDEAD,
    NET_TIME,
    NET_TIMEM,
    NET_END,
    NET_MSG,
    NET_UKN,
    NET_PARAM,
};

typedef std::queue<NetEvent_e> EventQueue;

#endif
