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

void Land::display(sf::RenderTarget& render) const
{
    for (const std::unique_ptr<ecs::IEntity>& entity : _entities)
        entity->display(render);
    for (const std::unique_ptr<Tile>& tile : _tiles)
        tile->display(render);
}

void Land::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::L)
            loadMap(CENTER_MAP(TEST_MAP.size()), TEST_MAP);
    }
}

void Land::loadMap(const sf::Vector2f& middle,
    const std::vector<std::vector<TileInfo_s>>& map)
{
    sf::Vector2f pos;
    std::srand(std::time({}));

    _tiles.clear();
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            pos = {middle.x - ((TILE_SIZE / 2) * (x + y)) + (TILE_SIZE * y), middle.y + (8 * (x + y))};
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

} // visual
} // gui
