/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.cpp
*/

#include "visual/interfaces/AScene.hpp"

#include "core/Engine.hpp"

namespace gui {
namespace visual {

AScene::AScene(const sf::FloatRect& rect) : _camera(rect)
{}

sf::View AScene::getView(void)
{
    return _camera;
}

void AScene::zoom(float scale)
{
    sf::Vector2f size = _camera.getSize();

    if (size.x * scale > core::DEFAULT_VIEW.width || size.y * scale < 0.0f)
        return;
    _camera.zoom(scale);
}

void AScene::move(const sf::Vector2f& factor)
{
    sf::Vector2f pos = _camera.getCenter();

    pos.x -= _camera.getSize().x / 2;
    pos.y -= _camera.getSize().y / 2;
    if (pos.x + factor.x + _camera.getSize().x > core::DEFAULT_VIEW.width ||
        pos.x + factor.x < 0)
        return;
    _camera.move(factor);
}

void AScene::move(float x, float y)
{
    sf::Vector2f pos = _camera.getCenter();

    pos.x -= _camera.getSize().x / 2;
    pos.y -= _camera.getSize().y / 2;
    if (pos.x + x + _camera.getSize().x > core::DEFAULT_VIEW.width ||
        pos.x + x < 0)
        return;
    _camera.move(sf::Vector2f(x, y));
}

} // visual
} // gui
