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
#include "ECSFactory.hpp"

namespace gui {
namespace visual {

Land::Land()
{
    std::srand(std::time({}));
}

void Land::display(sf::RenderTarget& render) const
{
    for (const auto& tileY : _tiles) {
        for (const auto& tileX : tileY.second) {
            tileX.second.tile->display(render);
            for (const auto& trantor : tileX.second.trantorians)
                trantor.second->display(render);
            for (const auto& resource : tileX.second.resources)
                resource->display(render);
        }
    }
    for (const std::unique_ptr<ecs::IEntity>& entity : _entities)
        entity->display(render);
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
    _tiles[x][y].tile = std::unique_ptr<Tile>(dynamic_cast<Tile*>(
            ecs::ECSFactory::createEntity(
                "tile",
                pos.x, pos.y,
                static_cast<int>(type)
            ).release()
    ));
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

void Land::addTrantorian(const network::NetPack& pack)
{
    int x = pack[1].getInt();
    int y = pack[2].getInt();
    sf::Vector2f pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);

    _tiles[x][y].trantorians[pack[0].getSize_t()] =
        std::unique_ptr<Trantorian>(dynamic_cast<Trantorian*>(
            ecs::ECSFactory::createEntity("trantorian", pos.x, pos.y).release()
        ));
}

} // visual
} // gui
