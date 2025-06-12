/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ResourceNode.cpp
*/

#include "ResourceNode.hpp"

namespace gui {
namespace visual {

ResourceNode::ResourceNode(const sf::Vector2f& pos, ResourceType_e type)
: AAnimated(pos, RESOURCE_NODE_TEXTURE.at(type), RESOURCE_RECT)
{
    _sprite.setOrigin(sf::Vector2f(RESOURCE_RECT.width / 2, RESOURCE_RECT.height));
    _sprite.setScale(sf::Vector2f(0.4, 0.4));
}

} // visual
} // gui
