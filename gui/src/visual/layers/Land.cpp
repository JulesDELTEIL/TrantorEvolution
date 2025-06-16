/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.cpp
*/

#include <iostream> // test purpose (to delete)
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
    for (const std::unique_ptr<Tile>& tile : _tiles)
        tile->display(render);
    for (const std::unique_ptr<Trantorian>& trantor : _trantorians)
        trantor->display(render);
    for (const std::unique_ptr<ecs::IEntity>& entity : _entities)
        entity->display(render);
}

void Land::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::L)
            loadMap(CENTER_MAP(TEST_MAP.size()), TEST_MAP);
        if (event.key.code == sf::Keyboard::T)
            addTrantorian(1, 1);
    }
}

void Land::loadMap(const sf::Vector2f& middle,
    const std::vector<std::vector<TileInfo_s>>& map)
{
    sf::Vector2f pos;

    _tiles.clear();
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            pos = MAP_POS(middle, x, y);
            if (map[y][x].type != EMPTY) {
                _tiles.emplace_back(dynamic_cast<Tile*>(
                        ecs::ECSFactory::createEntity(
                            "tile",
                            pos.x, pos.y,
                            static_cast<int>(map[y][x].type),
                            convertResource(map[y][x].resources)
                        ).release()
                ));
            }
        }
    }
}

uint8_t Land::convertResource(const std::array<bool, NB_RESOURCES>& resources)
{
    uint8_t infos = 0;

    for (uint8_t i = 0; i < NB_RESOURCES; ++i) {
        infos += resources[i];
        infos = infos << 1;
    }
    infos = infos << 1;
    return infos;
}

void Land::addTrantorian(int x, int y)
{
    sf::Vector2f pos = MAP_POS(CENTER_MAP(TEST_MAP.size()), x, y);

    _trantorians.emplace_back(dynamic_cast<Trantorian*>(
        ecs::ECSFactory::createEntity("trantorian", pos.x, pos.y).release()
    ));
}

} // visual
} // gui
