/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ResourceNode.cpp
*/

#include "visual/drawables/ResourceNode.hpp"

namespace gui {
namespace visual {

ResourceNode::ResourceNode(const sf::Vector2f& pos, ResourceType_e type)
: AAnimated(pos, RESOURCE_NODE_TEXTURE.at(type))
{
    
}

} // visual
} // gui
