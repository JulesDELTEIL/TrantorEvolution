/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.cpp
*/

#include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

Trantorian::Trantorian(const sf::Vector2f& pos, const sf::Vector2i& pos_in_map,
    size_t level, size_t team_id, const sf::Color& color) :
    _body(NB_TRANTORS),
    _type(NB_TRANTORS),
    _body_direction(NB_TRANTORS, FACE_RIGHT),
    _body_animation({
        std::ref(_body[0]), std::ref(_body[1]), std::ref(_body[2])
    }),
    _body_movement({
        std::ref(_body[0]), std::ref(_body[1]), std::ref(_body[2])
    })
{
    lvl = level;
    team = team_id;
    map_pos = pos_in_map;
    actual_pos = pos;
    for (size_t i = 0; i < NB_TRANTORS; ++i) {
        sf::Vector2f random_pos = {
            pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
            pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
        };
        _body[i].sprite.setOrigin(sf::Vector2f(32, 48));
        _body[i].sprite.setPosition(random_pos);
        _body[i].sprite.setColor(color);
        for (int d = 0; d < NB_BODY_ANIM; ++d)
            _body_animation[i].addAnimation(BODY_ANIM_INFOS[d]);
        _type[i] = IDLE;
        _body_animation[i].changeAnimation(_type[i]);
        _body[i].sprite.setScale(TRANTOR_SCALE, TRANTOR_SCALE);
    }
}

void Trantorian::draw(sf::RenderTarget& target, const sf::Clock& clock)
{
    static std::vector<bool> asked_type(NB_TRANTORS, false);

    for (size_t i = 0; i < NB_TRANTORS; ++i) {
        if (!_body_movement[i].move(clock)) {
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

void Trantorian::move(int index, const sf::Vector2f& new_pos, float time, const sf::Clock& clock)
{
    _body_animation[index].changeAnimation(WALK);
    if (_body_movement[index].changeDestination(new_pos, time, clock.getElapsedTime().asMilliseconds()) != _body_direction[index]) {
        sf::Vector2f scale = _body[index].sprite.getScale();
        _body[index].sprite.setScale(-scale.x, scale.y);
        if (_body_direction[index] == FACE_RIGHT)
            _body_direction[index] = FACE_LEFT;
        else
            _body_direction[index] = FACE_RIGHT;
    }
}

void Trantorian::collect(const std::shared_ptr<ResourceNode>& resource,
    float time, const sf::Clock& clock)
{
    int i = 0;
    std::vector<sf::Vector2f> res_pos = resource->getCollectPosition();
    resource_e type = resource->getType();

    for (const sf::Vector2f& to_go : res_pos) {
        if (type == WOOD)
            _type[i] = AXE;
        else if (type == STONE || type == CLAY ||
            type == METAL)
            _type[i] = PICKAXE;
        else
            _type[i] = COLLECT;
        move(i, to_go, time, clock);
        i += 1;
    }
}

void Trantorian::startIncantation(const std::shared_ptr<IncantationObject>& incantation_object,
    float time, const sf::Clock& clock)
{
    for (size_t index = 0; index < NB_TRANTORS; index++) {
        _type[index] = INCANT;
        move(index, incantation_object->getIncantationPosition(), time, clock);
    }
}

void Trantorian::endIncantation(const sf::Vector2f& pos,
    float time, const sf::Clock& clock)
{
    for (size_t index = 0; index < NB_TRANTORS; index++) {
        sf::Vector2f random_pos = {
            pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
            pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
        };
        _type[index] = IDLE;
        move(index, random_pos, time, clock);
    }
}

void Trantorian::layAnEgg()
{
    for (size_t index = 0; index < NB_TRANTORS; index++)
        _type[index] = IDLE;
    _type[0] = WATERING;
}

void Trantorian::laidAnEgg()
{
    size_t index = 0;

    for (size_t index = 0; index < NB_TRANTORS; index++)
        if (_type[index] == WATERING)
            break;
    _type[index] = IDLE;
}

ResourceGroup Trantorian::getInventory(void) const
{
    return _inventory;
}

void Trantorian::updateInventory(size_t q0, size_t q1, size_t q2, size_t q3, size_t q4, size_t q5, size_t q6)
{
    _inventory[FOOD] = q0;
    _inventory[WOOD] = q1;
    _inventory[STONE] = q2;
    _inventory[CLAY] = q3;
    _inventory[METAL] = q4;
    _inventory[OIL] = q5;
    _inventory[ANTI_MATTER] = q6;
}

void Trantorian::changeTile(const sf::Vector2f& new_pos, float time, const sf::Clock& clock)
{
    actual_pos = new_pos;
    for (size_t i = 0; i < NB_TRANTORS; ++i) {
        _type[i] = IDLE;
        sf::Vector2f random_pos = {
            new_pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
            new_pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
        };
        move(i, random_pos, time, clock);
    }
}

} // visual
} // gui
