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
    _body(NB_TRANTORS),
    _type(NB_TRANTORS),
    _body_animation({
        std::ref(_body[0]), std::ref(_body[1]), std::ref(_body[2]), std::ref(_body[3]), std::ref(_body[4]), std::ref(_body[5]), std::ref(_body[6])
    }),
    _body_movement({
        std::ref(_body[0]), std::ref(_body[1]), std::ref(_body[2]), std::ref(_body[3]), std::ref(_body[4]), std::ref(_body[5]), std::ref(_body[6])
    })
{
    lvl = level;
    map_pos = pos_in_map;
    for (size_t i = 0; i < NB_TRANTORS; ++i) {
        sf::Vector2f random_pos = {
            pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
            pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
        };
        _body[i].sprite.setPosition(random_pos);
        for (int d = 0; d < NB_BODY_ANIM; ++d) {
            _body_animation[i].addAnimation(BODY_ANIM_INFOS[d]);
        }
        _type[i] = IDLE;
        _body[i].sprite.setOrigin(sf::Vector2f(32, 48));
        _body_animation[i].changeAnimation(_type[i]);
        _body[i].sprite.setScale(TRANTOR_SCALE, TRANTOR_SCALE);
        _body_movement[i].changeDestination(pos, 0);
    }
}

void Trantorian::draw(sf::RenderTarget& target)
{
    static std::vector<bool> asked_type(NB_TRANTORS, false);

    for (size_t i = 0; i < NB_TRANTORS; ++i) {
        if (!_body_movement[i].move()) {
            if (!asked_type[i]) {
                asked_type[i] = true;
                _body_animation[i].changeAnimation(_type[i]);
            }
        } else
            asked_type[i] = false;
        _body_animation[i].animate();
        target.draw(_body[i].sprite);
    }
}

void Trantorian::collect(const std::vector<std::shared_ptr<ResourceNode>>& resources, float time)
{
    if (resources.size() > 0) {
        for (size_t i = 0; i < resources.size(); ++i) {
            _type[i] = COLLECT;
            _body_animation[i].changeAnimation(WALK);
            _body_movement[i].changeDestination(resources[i]->getCollectPosition(), time);
        }
    }
}

void Trantorian::move(const sf::Vector2f& new_pos, float time)
{
    for (size_t i = 0; i < NB_TRANTORS; ++i) {
        _type[i] = IDLE;
        sf::Vector2f random_pos = {
            new_pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
            new_pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
        };
        _body_animation[i].changeAnimation(WALK);
        _body_movement[i].changeDestination(random_pos, time);
    }
}

} // visual
} // gui
