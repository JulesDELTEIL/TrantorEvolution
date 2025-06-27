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

void AScene::zoom(float scale)
{
    _camera.zoom(scale);
}

void AScene::move(const sf::Vector2f& factor)
{
    _camera.move(factor);
}

void AScene::move(float x, float y)
{
    _camera.move(sf::Vector2f(x, y));
}

} // visual
} // gui
