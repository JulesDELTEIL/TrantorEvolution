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
    size_t level, const std::string& team_name) :
    _body(NB_TRANTORS),
    _type(NB_TRANTORS),
    _body_direction(NB_TRANTORS, FACE_RIGHT),
    _body_animation({
        std::ref(_body[0]), std::ref(_body[1]), std::ref(_body[2]), std::ref(_body[3]), std::ref(_body[4]), std::ref(_body[5]), std::ref(_body[6])
    }),
    _body_movement({
        std::ref(_body[0]), std::ref(_body[1]), std::ref(_body[2]), std::ref(_body[3]), std::ref(_body[4]), std::ref(_body[5]), std::ref(_body[6])
    })
{
    sf::Color team_color = generateTeamColor(team_name);

    lvl = level;
    team = team_name;
    map_pos = pos_in_map;
    actual_pos = pos;
    for (size_t i = 0; i < NB_TRANTORS; ++i) {
        sf::Vector2f random_pos = {
            pos.x + std::rand() % RES_RANGE_X + RES_MIN_X,
            pos.y + std::rand() % RES_RANGE_Y + RES_MIN_Y
        };
        _body[i].sprite.setOrigin(sf::Vector2f(32, 48));
        _body[i].sprite.setPosition(random_pos);
        _body[i].sprite.setColor(team_color);
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

sf::Color Trantorian::generateTeamColor(const std::string& team_name)
{
    size_t code = 0;
    sf::Color color;

    for (const char& chara : team_name)
        code += chara;
    code /= team_name.size();
    return sf::Color(code, code, code, 255);
}

void Trantorian::collect(const std::map<resource_e, std::shared_ptr<ResourceNode>>& resources,
    float time, const sf::Clock& clock)
{
    int i = 0;

    for (const auto& resource : resources) {
        if (resource.second->getQuantity() > 0) {
            if (resource.first == WOOD)
                _type[i] = AXE;
            else if (resource.first == STONE || resource.first == CLAY ||
                resource.first == METAL)
                _type[i] = PICKAXE;
            else
                _type[i] = COLLECT;
            move(i, resource.second->getCollectPosition(), time, clock);
        }
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


ResourceGroup Trantorian::getInventory(void) const
{
    return _inventory;
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
