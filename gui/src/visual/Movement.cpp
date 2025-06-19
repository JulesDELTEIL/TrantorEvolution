/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Movement.cpp
*/

#include <cmath>

#include "visual/Movement.hpp"

namespace gui {
namespace visual {

Movement::Movement(std::reference_wrapper<Drawable> drawable) : _drawable(drawable)
{

}

void Movement::changeDestination(const sf::Vector2f& new_pos, float time_ms)
{
    sf::Vector2f sprite_pos = _drawable.get().sprite.getPosition();

    _direction = {new_pos.x - sprite_pos.x, new_pos.y - sprite_pos.y};
    _to_go = new_pos;
    _time = time_ms;
    _clock.restart();
}

void Movement::move(void)
{
    if (_drawable.get().sprite.getPosition() == _to_go)
        return;
    float percent = _clock.getElapsedTime().asMilliseconds() / _time;
 
    _drawable.get().sprite.setPosition(_direction * percent);
    _clock.restart();
}

} // visual
} // gui