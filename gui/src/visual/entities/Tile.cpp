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

Tile::Tile(const sf::Vector2f& pos, BiomeTypes_e type) : AEntity(pos)
{
    _drawables["background"] = ecs::ECSFactory::createDraw("biome", pos.x, pos.y, static_cast<int>(type));
}

void Tile::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables) {
        drawable.second->draw(win);
    }
}

void Tile::event(int)
{

}

} // visual
} // gui
