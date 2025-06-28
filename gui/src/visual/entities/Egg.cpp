/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg.cpp
*/

#include "visual/entities/Egg.hpp"

namespace gui {
namespace visual {

Egg::Egg(const sf::Vector2f& pos)
: _hatching(false) {

    _egg.texture.loadFromFile(EGG_ANIM_INFO.path);
    _egg.sprite.setPosition(pos);
    _egg.sprite.setTexture(_egg.texture);
    _rect.width = EGG_ANIM_INFO.frame_size.x;
    _rect.height = EGG_ANIM_INFO.frame_size.y;
    _egg.sprite.setTextureRect(_rect);
    _egg.sprite.setOrigin(sf::Vector2f(_rect.width / 2, _rect.height));
    _egg.sprite.setScale(0.5, 0.4);
}

void Egg::draw(sf::RenderTarget& target)
{
    if (_clock.getElapsedTime().asSeconds() > EGG_ANIM_INFO.delta && _hatching) {
        _rect.left += EGG_ANIM_INFO.frame_size.x;
        _egg.sprite.setTextureRect(_rect);
        _clock.restart();
        if (_rect.left >= int(EGG_ANIM_INFO.frame_size.x * EGG_ANIM_INFO.max_frame.x))
            _hatching = false;
    }
    target.draw(_egg.sprite);
}

void Egg::hatch()
{
    _clock.restart();
    _hatching = true;
}

} // gui
} // visual
