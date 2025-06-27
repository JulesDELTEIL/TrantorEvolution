/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ResourceNode.cpp
*/

#include "visual/entities/ResourceNode.hpp"

namespace gui {
namespace visual {

ResourceNode::ResourceNode(const sf::Vector2f& pos, resource_e type, size_t quantity)
{
    _type = type;
    _pos = pos;
    _resource.texture.loadFromFile(RESOURCE_NODE_TEXTURE.at(_type));
    _resource.sprite.setTexture(_resource.texture);
    _resource.sprite.setTextureRect(RESOURCE_RECT);
    _resource.sprite.setOrigin(sf::Vector2f(RESOURCE_RECT.width / 2, RESOURCE_RECT.height));
    _resource.sprite.setScale(RES_SCALE, RES_SCALE);
    updateQuantity(quantity);
}

void ResourceNode::addResource(void)
{
    sf::Vector2f res_pos = {
        _pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
        _pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
    };
    _sprites_pos.push_back(res_pos);
}

void ResourceNode::draw(sf::RenderTarget& target)
{
    if (_quantity > 0) {
        for (size_t i = 0; i < _sprites_pos.size(); ++i) {
            _resource.sprite.setPosition(_sprites_pos[i]);
            target.draw(_resource.sprite);
        }
    }
}

std::vector<sf::Vector2f> ResourceNode::getCollectPosition(void)
{
    std::vector<sf::Vector2f> resources_pos = {};

    for (size_t i = 0; i < _sprites_pos.size(); ++i)
        resources_pos.push_back(_sprites_pos[i] + sf::Vector2f(-4, 0));
    return resources_pos;
}

void ResourceNode::updateQuantity(size_t new_quantity)
{
    size_t nb_sprites = new_quantity;

    _quantity = new_quantity;
    if (nb_sprites > 3)
        nb_sprites = 3;
    if (nb_sprites > _sprites_pos.size()) {
        for (size_t i = _sprites_pos.size(); i < nb_sprites; ++i)
            addResource();
    } else if (nb_sprites < _sprites_pos.size()) {
        for (size_t i = _sprites_pos.size(); i > nb_sprites; --i)
            _sprites_pos.pop_back();
    }
}

void ResourceNode::lowerQuantity(size_t to_lower)
{
    if (to_lower > _quantity)
        _quantity = 0;
    else
        _quantity -= to_lower;
    updateQuantity(_quantity);
}

resource_e ResourceNode::getType(void) const
{
    return _type;
}

size_t ResourceNode::getQuantity(void) const
{
    return _quantity;
}

} // visual
} // gui
