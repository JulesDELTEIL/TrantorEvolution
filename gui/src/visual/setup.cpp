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

std::unique_ptr<ecs::IDrawable> makeBody(float x, float y)
{
    return std::make_unique<visual::Body>(sf::Vector2f(x, y));
}

std::unique_ptr<ecs::IEntity> makeTile(float x, float y, int type, uint8_t resources)
{
    std::vector<ResourceType_e> resources_casted;

    resources = resources >> (8 - NB_RESOURCES);
    for (uint8_t i = 0; i < NB_RESOURCES; ++i) {
        resources = resources >> 1;
        if (resources % 2)
            resources_casted.push_back(static_cast<ResourceType_e>(i));
    }
    return std::make_unique<visual::Tile>(sf::Vector2f(x, y), static_cast<visual::BiomeTypes_e>(type), resources_casted);
}

std::unique_ptr<ecs::IEntity> makeTrantorian(float x, float y)
{
    return std::make_unique<visual::Trantorian>(sf::Vector2f(x, y));
}

} // namespace visual
} // namespace gui
