/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ResourceNode.cpp
*/

#include "visual/entities/ResourceNode.hpp"

namespace gui {
namespace visual {

ResourceNode::ResourceNode(const sf::Vector2f& pos, ResourceType_e type, size_t quantity)
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
    _quantity = quantity;
    _resource.sprite.setScale(
        MIN_SCALE + _quantity / SCALE_RATIO,
        MIN_SCALE + _quantity / SCALE_RATIO
    );
}

void ResourceNode::draw(sf::RenderTarget& target)
{
    target.draw(_resource.sprite);
}

sf::Vector2f ResourceNode::getCollectPosition(void)
{
    return _resource.sprite.getPosition() + sf::Vector2f(-5, 0);
}

void ResourceNode::addQuantity(size_t to_add)
{
    sf::Vector2f scale;
    size_t new_quantity = to_add + _quantity;

    _quantity = new_quantity;
    if (new_quantity > SCALE_RATIO)
        new_quantity = SCALE_RATIO;
    scale.x = MIN_SCALE + new_quantity / SCALE_RATIO;
    scale.y = MIN_SCALE + new_quantity / SCALE_RATIO;
    _resource.sprite.setScale(scale);
}

} // visual
} // gui
