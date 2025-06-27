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
    #include <string>

namespace gui {
namespace network {

enum NetEvent_e {
    NONE = 0,
    CON,
    CLIENTID,
    INITMSIZE,
    MSIZE,
    TILE,
    MAP,
    TEAMS,
    NEW,
    PPOS,
    PLVL,
    PINV,
    PUSH,
    CAST,
    PINC,
    PEINC,
    PEGG,
    PDROP,
    PGET,
    PDEAD,
    ELAID,
    ENEW,
    EDEAD,
    TIME,
    TIMEM,
    END,
    MSG,
    UKN,
    PARAM,
    BIOME,
};

class NetType {
    public:
        NetType(const std::string& value);
        
        size_t getSize_t(void) const;
        float getFloat(void) const;
        int getInt(void) const;
        std::string getString(void) const;

    private:
        std::string _value;
};

typedef std::vector<NetType> NetPack;

struct NetEventPack {
    NetEvent_e event;
    NetPack pack;
};

typedef std::queue<NetEventPack> PackQueue;

static const std::map<std::string, NetEvent_e> CODE_EVENT_LINK {
    {"WELCOME", CON},
    {"msz", MSIZE},
    {"bct", TILE},
    {"tna", TEAMS},
    {"pnw", NEW},
    {"ppo", PPOS},
    {"plv", PLVL},
    {"pin", PINV},
    {"pex", PUSH},
    {"pbc", CAST},
    {"pic", PINC},
    {"pie", PEINC},
    {"pfk", PEGG},
    {"pdr", PDROP},
    {"pgt", PGET},
    {"pdi", PDEAD},
    {"enw", ELAID},
    {"ebo", ENEW},
    {"edi", EDEAD},
    {"sgt", TIME},
    {"sst", TIMEM},
    {"seg", END},
    {"smg", MSG},
    {"suc", UKN},
    {"sbp", PARAM},
    {"bio", BIOME}
};

typedef std::pair<std::string, NetPack> Command;

} // network
} // gui

#endif
