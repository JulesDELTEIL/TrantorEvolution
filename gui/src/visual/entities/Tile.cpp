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
    _drawables["background"] = ecs::ECSFactory::createDraw("biome", pos.x, pos.y, static_cast<int>(type));
    for (const ResourceType_e& res : resources) {
        sf::Vector2f res_pos = {pos.x + std::rand() % RES_RANGE_X + RES_MIN_X, pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y};
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
