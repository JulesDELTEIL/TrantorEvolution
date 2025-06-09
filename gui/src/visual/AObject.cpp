/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AObject.cpp
*/

#include "visual/AObject.hpp"

namespace gui {
namespace visual {

AObject::AObject(const sf::Vector2f& entity_origin,
    const std::string& path) : ADrawable(entity_origin), sf::Sprite()
{
    _type = ANIMATED;
    if (!path.empty())
        _texture.loadFromFile(path);
    setTexture(_texture);
    this->setPosition(entity_origin);
}

} // visual
} // gui
