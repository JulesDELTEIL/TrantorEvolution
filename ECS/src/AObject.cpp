/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AObject.cpp
*/

#include "interfaces/AObject.hpp"

namespace ecs {

AObject::AObject(const sf::Vector2f& pos, const std::string& path, const sf::IntRect& rect) :
    ADrawable(pos)
{
    if (!path.empty())
        _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    _sprite.setPosition(pos);
    _sprite.setTextureRect(rect);
}

void AObject::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(_sprite);
}

void AObject::setPosition(const sf::Vector2f& pos)
{
    _sprite.setPosition(pos);
}

sf::Vector2f AObject::getPosition(void) const
{
    return _sprite.getPosition();
}

void AObject::setRotation(float angle)
{
    _sprite.setRotation(angle);
}

float AObject::getRotation(void) const
{
    return _sprite.getRotation();
}

} // ecs
