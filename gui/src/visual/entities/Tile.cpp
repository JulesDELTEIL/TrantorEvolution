/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.cpp
*/

#include <cstdlib>

#include "visual/entities/Tile.hpp"
#include "ECSFactory.hpp"

namespace gui {
namespace visual {

Tile::Tile(const sf::Vector2f& pos, BiomeTypes_e type,
    const std::vector<ResourceType_e>& resources) : AEntity(pos)
{
    int rangeX = 25 - 8 + 1;
    int rangeY = 9 - 4 + 1;

    _drawables["background"] = ecs::ECSFactory::createDraw("biome", pos.x, pos.y, static_cast<int>(type));
    for (const ResourceType_e& res : resources) {
        sf::Vector2f res_pos = {pos.x + std::rand() % rangeX + 8, pos.y + std::rand() % rangeY + 4};
        _drawables["resource_node" + res] = ecs::ECSFactory::createDraw("resource_node", res_pos.x, res_pos.y, static_cast<int>(res));
    }
}

void Tile::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables) {
        win.draw(*drawable.second);
    }
}

void Tile::event(const sf::Event&)
{

}


} // visual
} // gui
