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
    for (auto& tileY : _tiles) {
        for (auto& tileX : tileY.second) {
            tileX.second.tile->draw(render);
            for (auto& trantor : tileX.second.trantorians) {
                trantor.second->draw(render);
            }
        }
    }
}

void Land::event(const sf::Event&, const network::NetEventPack& net_pack)
{
    switch (static_cast<int>(net_pack.event)) {
        case network::MSIZE:
            _map_size = sf::Vector2f(net_pack.pack[0].getFloat(), net_pack.pack[1].getFloat());
            break;
        case network::MAP:
            if (!_map_set && _map_size.y != -1)
                loadTile(CENTER_MAP(_map_size.y), net_pack.pack);
            else
                updateTile(net_pack.pack);
            break;
        case network::NEW:
            addTrantorian(net_pack.pack);
            break;
        case network::PUSH | network::CAST :
            trantorianAction(net_pack);
    }
}

void Land::loadTile(const sf::Vector2f& middle, const network::NetPack& pack)
{
    static int index = 0;
    sf::Vector2f pos = {0, 0};
    BiomeTypes_e type = EMPTY;

    int x = pack[0].getInt();
    int y = pack[1].getInt();
    pos = MAP_POS(middle, x, y);
    type = readBiomeType(pack);
    _tiles[x][y].tile = std::make_unique<Tile>(pos, type);
    for (size_t i = 2; i < NB_MAP_ARG; ++i) {
        for (size_t d = 0; d < pack[i].getSize_t(); ++d)
            addResourceInTile(x, y, pos, static_cast<ResourceType_e>(i - 2));
    }
    index += 1;
    if (index >= (_map_size.x * _map_size.y))
        _map_set = true;
}

void Land::updateTile(const network::NetPack&)
{

}

BiomeTypes_e Land::readBiomeType(const network::NetPack&)
{
    return BiomeTypes_e::GRASS;
}

void Land::addResourceInTile(int x, int y, const sf::Vector2f& pos, ResourceType_e type)
{
    _tiles[x][y].resources.emplace_back(std::make_unique<ResourceNode>(pos, type));
}

void Land::addTrantorian(const network::NetPack& pack)
{
    int x = pack[1].getInt();
    int y = pack[2].getInt();
    sf::Vector2f pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    std::shared_ptr<Trantorian> newT = std::make_shared<Trantorian>(pos);

    _tiles[x][y].trantorians[pack[0].getSize_t()] = newT;
    _trantorians[pack[0].getSize_t()] = newT;
}

void Land::trantorianAction(const network::NetEventPack& pack)
{
    int id = pack.pack[0].getInt();
}

} // visual
} // gui
