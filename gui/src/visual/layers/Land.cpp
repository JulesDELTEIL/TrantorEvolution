/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.cpp
*/

#include <cstdlib>
#include <ctime>

#include "visual/layers/Land.hpp"
#include "visual/visual.hpp"

namespace gui {
namespace visual {

Land::Land()
{
    std::srand(std::time({}));
}

void Land::display(sf::RenderTarget& render)
{
    clearResources();
    for (auto& tileY : _tiles) {
        for (auto& tileX : tileY.second) {
            tileX.second.tile->draw(render);
            for (auto& trantor : tileX.second.trantorians)
                trantor.second->draw(render);
            for (auto& resource : tileX.second.resources)
                resource->draw(render);
        }
    }
}

void Land::event(const sf::Event&, const network::NetEventPack& net_pack)
{
    switch (static_cast<int>(net_pack.event)) {
        case network::MSIZE:
            _map_size = sf::Vector2f(net_pack.pack[0].getFloat(), net_pack.pack[1].getFloat());
            break;
        case network::TILE:
            if (!_map_set && _map_size.y != -1)
                loadTile(net_pack.pack);
            else
                updateTile(net_pack.pack);
            break;
        case network::NEW:
            addTrantorian(net_pack.pack);
            break;
        case network::PPOS:
            posTrantorian(net_pack.pack);
            break;
        case network::PGET:
            float time = ACT_TIME(7);
            sf::Vector2i tile_pos = {_trantorians.at(net_pack.pack[0].getSize_t())->map_pos.x, _trantorians.at(net_pack.pack[0].getSize_t())->map_pos.y};
            _trantorians.at(net_pack.pack[0].getSize_t())->collect(_tiles[tile_pos.x][tile_pos.y].resources, time / 2);
            _clear_resources.push_back({time + _clock.getElapsedTime().asMilliseconds(), tile_pos});
            break;
    }
}

void Land::loadTile(const network::NetPack& pack)
{
    static int index = 0;
    sf::Vector2f pos = {0, 0};
    BiomeTypes_e type = EMPTY;

    int x = pack[0].getInt();
    int y = pack[1].getInt();
    pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    type = readBiomeType(pack);
    _tiles[x][y].tile = std::make_unique<Tile>(pos, type);
    for (size_t i = 2; i < NB_MAP_ARG; ++i)
        addResourceInTile(x, y, pos, static_cast<ResourceType_e>(i - 2), pack[i].getSize_t());
    index += 1;
    if (index >= (_map_size.x * _map_size.y))
        _map_set = true;
}

BiomeTypes_e Land::readBiomeType(const network::NetPack&)
{
    return BiomeTypes_e::GRASS;
}

void Land::updateTile(const network::NetPack& pack)
{
    sf::Vector2f pos = {0.0f, 0.0f};

    int x = pack[0].getInt();
    int y = pack[1].getInt();
    pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    for (size_t i = 2; i < NB_MAP_ARG; ++i)
        addResourceInTile(x, y, pos, static_cast<ResourceType_e>(i - 2), pack[i].getSize_t());
}

void Land::addResourceInTile(int x, int y, const sf::Vector2f& pos, ResourceType_e type, size_t quantity)
{
    if (quantity > 0)
        _tiles[x][y].resources.emplace_back(std::make_shared<ResourceNode>(pos, type, quantity));
}

void Land::clearResources(void)
{
    for (ClearTile& to_clear : _clear_resources) {
        if (_clock.getElapsedTime().asMilliseconds() >= to_clear.time)
            _tiles[to_clear.tile.x][to_clear.tile.y].resources.clear();
    }
}

void Land::addTrantorian(const network::NetPack& pack)
{
    int x = pack[1].getInt();
    int y = pack[2].getInt();
    sf::Vector2f pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    pos.y += TILE_SIZE / 4;
    std::shared_ptr<Trantorian> newT = std::make_shared<Trantorian>(pos, sf::Vector2i(x, y), pack[4].getSize_t());

    _tiles[x][y].trantorians[pack[0].getSize_t()] = newT;
    _trantorians[pack[0].getSize_t()] = newT;
}

void Land::posTrantorian(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();
    std::shared_ptr<Trantorian> trantor = _trantorians.at(id);
    int x = pack[1].getInt();
    int y = pack[2].getInt();
    sf::Vector2f pos;

    if (trantor->map_pos.x != x || trantor->map_pos.y != y) {
        pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
        pos.y += TILE_SIZE / 4;
        trantor->move(pos, ACT_TIME(7));
        _tiles[trantor->map_pos.x][trantor->map_pos.y].trantorians.erase(id);
        trantor->map_pos = {x, y};
        _tiles[x][y].trantorians[id] = trantor;
    }
}

} // visual
} // gui
