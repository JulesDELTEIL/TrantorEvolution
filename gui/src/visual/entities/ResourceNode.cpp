/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ResourceNode.cpp
*/

#include "visual/entities/ResourceNode.hpp"

namespace gui {
namespace visual {

ResourceNode::ResourceNode(const sf::Vector2f& pos, ResourceType_e type)
{
    sf::Vector2f res_pos = {
        pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
        pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
    };
    _resource.texture.loadFromFile(RESOURCE_NODE_TEXTURE.at(type));
    _resource.sprite.setPosition(res_pos);
    _resource.sprite.setTexture(_resource.texture);
    _resource.sprite.setTextureRect(RESOURCE_RECT);
    _resource.sprite.setOrigin(sf::Vector2f(RESOURCE_RECT.width / 2, RESOURCE_RECT.height));
    _resource.sprite.setScale(0.4, 0.4);
}

void ResourceNode::draw(sf::RenderTarget& target)
{
    target.draw(_resource.sprite);
}

} // visual
} // gui
