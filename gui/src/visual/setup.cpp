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

std::unique_ptr<ecs::IDrawable> makeResource(float x, float y, int type)
{
    return std::make_unique<visual::Resource>(sf::Vector2f(x, y), static_cast<visual::ResourceType_e>(type));
}

std::unique_ptr<ecs::IDrawable> makeBody(float x, float y)
{
    return std::make_unique<visual::Body>(sf::Vector2f(x, y));
}

std::unique_ptr<ecs::IEntity> makeTile(float x, float y, int type)
{
    return std::make_unique<visual::Tile>(sf::Vector2f(x, y), static_cast<visual::BiomeTypes_e>(type));
}

std::unique_ptr<ecs::IEntity> makeTrantorian(float x, float y)
{
    return std::make_unique<visual::Trantorian>(sf::Vector2f(x, y));
}

std::unique_ptr<ecs::IEntity> makeResourceNode(float x, float y, int type)
{
    return std::make_unique<visual::ResourceNode>(sf::Vector2f(x, y), static_cast<visual::ResourceType_e>(type));
}

} // namespace visual
} // namespace gui
