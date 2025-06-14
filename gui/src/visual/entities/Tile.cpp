/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.cpp
*/

#include "visual/entities/Tile.hpp"
#include "ECSFactory.hpp"

namespace gui {
namespace visual {

Tile::Tile(const sf::Vector2f& pos, BiomeTypes_e type) : AEntity(pos)
{
    _drawables["background"] = ecs::ECSFactory::createDraw("biome", pos.x, pos.y, static_cast<int>(type));
    if (type == GRASS)
        _drawables["tree"] = ecs::ECSFactory::createDraw("resource_node", pos.x + 8.0f, pos.y + 8.0f, static_cast<int>(WOOD));
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
