/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ResourceNode.cpp
*/

#include "visual/entities/ResourceNode.hpp"
#include "ECSFactory.hpp"

namespace gui {
namespace visual {

ResourceNode::ResourceNode(const sf::Vector2f& pos, ResourceType_e type) : AEntity(pos)
{
    sf::Vector2f res_pos = {
        pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
        pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
    };
    _drawables["resource"] = ecs::ECSFactory::createDraw("resource", res_pos.x, res_pos.y, static_cast<int>(type));
}

void ResourceNode::display(sf::RenderTarget& render) const
{
    for (const auto& drawable : _drawables)
        drawable.second->draw(render);
}

void ResourceNode::event(const sf::Event&)
{

}


} // visual
} // gui
