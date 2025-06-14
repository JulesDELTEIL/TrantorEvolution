/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** setup.cpp
*/

#include "visual/setup.hpp"

namespace gui {
namespace visual {
    
std::unique_ptr<ecs::IDrawable> makeBiome(float x, float y, int type)
{
    return std::make_unique<visual::Biome>(sf::Vector2f(x, y), static_cast<visual::BiomeTypes_e>(type));
}

std::unique_ptr<ecs::IDrawable> makeResourceNode(float x, float y, int type)
{
    return std::make_unique<visual::ResourceNode>(sf::Vector2f(x, y), static_cast<visual::ResourceType_e>(type));
}

std::unique_ptr<ecs::IEntity> makeTile(float x, float y, int type)
{
    return std::make_unique<visual::Tile>(sf::Vector2f(x, y), static_cast<visual::BiomeTypes_e>(type));
}

} // namespace visual
} // namespace gui
