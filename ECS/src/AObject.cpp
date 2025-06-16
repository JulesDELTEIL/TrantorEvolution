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

void AObject::draw(sf::RenderTarget& target)
{
    target.draw(_sprite);
}

void AObject::setPosition(const sf::Vector2f& pos)
{
    _pos = pos;
    _sprite.setPosition(pos);
}

sf::Vector2f AObject::getPosition(void) const
{
    return _sprite.getPosition();
}

void AObject::setScale(const sf::Vector2f& scale)
{
    _sprite.setScale(scale);
}

sf::Vector2f AObject::getScale(void) const
{
    return _sprite.getScale();
}

} // ecs
