/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Movement.cpp
*/

#include <iostream> // test purpose (to delete)

#include "visual/Movement.hpp"

namespace gui {
namespace visual {

Movement::Movement(std::reference_wrapper<Drawable> drawable) : _drawable(drawable)
{

}

int Movement::changeDestination(const sf::Vector2f& new_pos, float time_ms, float start)
{
    sf::Vector2f sprite_pos = _drawable.get().sprite.getPosition();

    _direction = {new_pos.x - sprite_pos.x, new_pos.y - sprite_pos.y};
    _time = time_ms;
    _start = start;
    _last_time = _start;
    if (new_pos.x < sprite_pos.x)
        return FACE_LEFT;
    return FACE_RIGHT;
}

bool Movement::move(const sf::Clock& clock)
{
    float time_elapsed = clock.getElapsedTime().asMilliseconds();
    float percent = 0;

    if (time_elapsed < _start + _time) {
        percent = (time_elapsed - _last_time) / _time;
        _drawable.get().sprite.setPosition(
            _drawable.get().sprite.getPosition() + _direction * percent
        );
        _last_time = time_elapsed;
        return true;
    }
    return false;
}

} // visual
} // gui