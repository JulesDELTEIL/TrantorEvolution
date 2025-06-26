/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** IncantationObject.cpp
*/

#include "visual/entities/IncantationObject.hpp"
#include <iostream>

namespace gui {
namespace visual {

IncantationObject::IncantationObject(const sf::Vector2f& pos)
: _left_side(false) {
    sf::Vector2f res_pos = {
        pos.x + std::rand() % INCANTATION_RES_RANGE_X + INCANTATION_RES_MIN_X,
        pos.y + std::rand() % INCANTATION_RES_RANGE_Y + INCANTATION_RES_MIN_Y
    };
    _pedestal.texture.loadFromFile(PEDESTAL_TEXTURE);
    _pedestal.sprite.setPosition(res_pos);
    _pedestal.sprite.setTexture(_pedestal.texture);
    _pedestal.sprite.setTextureRect(PEDESTAL_RECT);
    _pedestal.sprite.setOrigin(sf::Vector2f(PEDESTAL_RECT.width / 2, PEDESTAL_RECT.height));
}

void IncantationObject::draw(sf::RenderTarget& target)
{
    target.draw(_pedestal.sprite);
}

sf::Vector2f IncantationObject::getIncantationPosition(void)
{
    _left_side = !_left_side;
    return _pedestal.sprite.getPosition() + sf::Vector2f(-2 + 10 * _left_side, 0);
}

} // visual
} // gui