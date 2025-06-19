/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.cpp
*/

#include <iostream> // test purpose (to delete)

#include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

Trantorian::Trantorian(const sf::Vector2f& pos) :
    _body_animation(std::ref(_body)), _body_movement(std::ref(_body))
{
    _body.sprite.setPosition(pos);
    for (int i = 0; i < NB_BODY_ANIM; ++i)
        _body_animation.addAnimation(BODY_ANIM_INFOS[i]);
    _body_animation.changeAnimation(IDLE);
    _body.sprite.setScale(0.2, 0.2);
    _body_movement.changeDestination(pos, 0);
}

void Trantorian::draw(sf::RenderTarget& target)
{
    _body_animation.animate();
    _body_movement.move();
    target.draw(_body.sprite);
}

void Trantorian::collect(void)
{
    _body_movement.changeDestination({0.0f, 0.0f}, 1000.0f);
    _body_animation.changeAnimation(COLLECT);
}

void Trantorian::move(const sf::Vector2f& factor, float time)
{
    _body_animation.changeAnimation(WALK);
    _body_movement.changeDestination(_body.sprite.getPosition() + factor, time);
}

} // visual
} // gui
