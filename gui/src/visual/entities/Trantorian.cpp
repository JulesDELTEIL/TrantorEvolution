/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.cpp
*/

#include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

Trantorian::Trantorian(const sf::Vector2f& pos) : _body_animation(std::ref(_body))
{
    for (int i = 0; i < NB_BODY_ANIM; ++i)
        _body_animation.addAnimation(BODY_ANIM_INFOS[i]);
    _body_animation.changeAnimation(WALK);
    _body.sprite.setScale(0.2, 0.2);
    _body.sprite.setPosition(pos);
}

void Trantorian::draw(sf::RenderTarget& target)
{
    _body_animation.animate();
    target.draw(_body.sprite);
}

void Trantorian::collect(void)
{
    _body_animation.changeAnimation(COLLECT);
}

} // visual
} // gui
