/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.cpp
*/

#include "visual/interfaces/AScene.hpp"

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
