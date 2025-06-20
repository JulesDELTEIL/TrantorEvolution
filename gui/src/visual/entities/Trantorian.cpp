/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.cpp
*/

#include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

Trantorian::Trantorian(const sf::Vector2f& pos, const sf::Vector2i& pos_in_map, size_t level) :
    _body_animation(std::ref(_body)), _body_movement(std::ref(_body))
{
    _lvl = level;
    map_pos = pos_in_map;
    _body.sprite.setPosition(pos);
    for (int i = 0; i < NB_BODY_ANIM; ++i)
        _body_animation.addAnimation(BODY_ANIM_INFOS[i]);
    _type = IDLE;
    _body.sprite.setOrigin(sf::Vector2f(32, 48));
    _body_animation.changeAnimation(_type);
    _body.sprite.setScale(0.2, 0.2);
    _body_movement.changeDestination(pos, 0);
}

void Trantorian::draw(sf::RenderTarget& target)
{
    static bool asked_type = false;

    if (!_body_movement.move()) {
        if (!asked_type) {
            asked_type = true;
            _body_animation.changeAnimation(_type);
        }
    } else
        asked_type = false;
    _body_animation.animate();
    target.draw(_body.sprite);
}

void Trantorian::collect(const std::vector<std::shared_ptr<ResourceNode>>& resources, float time)
{
    if (resources.size() > 0) {
        _type = COLLECT;
        _body_animation.changeAnimation(WALK);
        _body_movement.changeDestination(resources[0]->getCollectPosition(), time);
    }
}

void Trantorian::move(const sf::Vector2f& new_pos, float time)
{
    _type = IDLE;
    _body_animation.changeAnimation(WALK);
    _body_movement.changeDestination(new_pos, time);
}

} // visual
} // gui
