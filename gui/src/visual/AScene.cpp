/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.cpp
*/

#include "visual/AScene.hpp"

#include "core/Engine.hpp"

namespace gui {
namespace visual {

AScene::AScene(const sf::FloatRect& rect) : _camera(rect)
{}

sf::View AScene::getView(void)
{
    return _camera;
}

sf::Vector2f AScene::getViewPos(void) const
{
    sf::Vector2f pos = _camera.getCenter();
    sf::Vector2f size = _camera.getSize();

    pos.x -= size.x / 2;
    pos.y -= size.y / 2;
    return pos;
}

void AScene::changeViewDest(const sf::Vector2f& new_dest, float time_ms)
{
    sf::Vector2f pos = _camera.getCenter();

    if (new_dest.x < 0 || new_dest.y < 0)
        return;
    _direction = {new_dest.x - pos.x, new_dest.y - pos.y};
    _time = time_ms;
    _start = _clock.getElapsedTime().asMilliseconds();
    _last_time = _start;
}

void AScene::moveToDest(void)
{
    float time_elapsed = _clock.getElapsedTime().asMilliseconds();
    float percent = 0;

    if (time_elapsed < _start + _time) {
        percent = (time_elapsed - _last_time) / _time;
        _camera.move(_direction);
        _last_time = time_elapsed;
    }
}

void AScene::zoom(float scale)
{
    _zoom *= scale;
    _camera.zoom(scale);
}

void AScene::move(const sf::Vector2f& factor)
{
    _camera.move(factor * _zoom);
}

void AScene::move(float x, float y)
{
    _camera.move(sf::Vector2f(x * _zoom, y * _zoom));
}

} // visual
} // gui
