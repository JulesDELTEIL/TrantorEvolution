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
    NET_NONE = 0,
    NET_CON,
    NET_CLIENTID,
    NET_INITMSIZE,
    NET_MSIZE,
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
    NET_PEINC,
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

typedef std::vector<float> NetPack;

struct NetEventPack {
    NetEvent_e event;
    NetPack pack;
};

typedef std::queue<NetEventPack> PackQueue;

class NetType {
    public:
    NetType(const std::string& value) : _value(value) {}
    
    size_t getSize_t(void);
    float getFloat(void);
    int getInt(void);
    std::string getString(void);

    private:
        std::string _value;
};

static const std::map<std::string, NetEvent_e> CODE_EVENT_LINK {
    {"msz", NET_MSIZE},
    {"bct", NET_TILE},
    {"tna", NET_TEAMS},
    {"pnw", NET_NEW},
    {"ppo", NET_PPOS},
    {"plv", NET_PLVL},
    {"pin", NET_PINV},
    {"pex", NET_PUSH},
    {"pbc", NET_CAST},
    {"pic", NET_PINC},
    {"pie", NET_PEINC},
    {"pfk", NET_PEGG},
    {"pdr", NET_PDROP},
    {"pgt", NET_PGET},
    {"pdi", NET_PDEAD},
    {"enw", NET_ELAID},
    {"ebo", NET_ENEW},
    {"edi", NET_EDEAD},
    {"sgt", NET_TIME},
    {"sst", NET_TIMEM},
    {"seg", NET_END},
    {"smg", NET_MSG},
    {"suc", NET_UKN},
    {"sbp", NET_PARAM}
};

} // network
} // gui

#endif
