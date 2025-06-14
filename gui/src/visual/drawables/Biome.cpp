/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Biome.cpp
*/

#include "visual/drawables/Biome.hpp"

namespace gui {
namespace visual {

Biome::Biome(const sf::Vector2f& pos, BiomeTypes_e type) : AObject(pos, BIOME_TEXTURE_PATH, TEXTURE_RECT.at(type))
{

}

} // visual
} // gui
