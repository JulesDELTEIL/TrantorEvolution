/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** LoadingScreen.cpp
*/

#include <iostream>

#include "visual/entities/LoadingScreen.hpp"

namespace gui {
namespace visual {

LoadingScreen::LoadingScreen(const sf::FloatRect& rect) : _bar(LOAD_BAR_PATH, LOAD_BAR_SCALE),
    _background(LOAD_BG_PATH)
{
    sf::Vector2u size = _bar.texture.getSize();
    sf::Vector2f pos = {
        (rect.width / 2) + rect.left - (size.x * LOAD_BAR_SCALE / 2),
        (rect.height / 2) + rect.top - (size.y * LOAD_BAR_SCALE / 2)
    };

    _bar_size = {size.x * LOAD_BAR_SCALE - 40.0f, size.y * LOAD_BAR_SCALE - 20.0f};
    _bar.sprite.setPosition(pos);
    _load_done.setFillColor(sf::Color(233, 187, 0));
    _load_done.setPosition(pos + sf::Vector2f(20.0f, 5.0f));
    _load_done.setSize({0.0f, _bar_size.y});
    _background.sprite.setPosition(rect.left, rect.top);
}

void LoadingScreen::draw(sf::RenderTarget& render)
{
    render.draw(_background.sprite);
    render.draw(_load_done);
    render.draw(_bar.sprite);
}

void LoadingScreen::loadingPercent(float percent)
{
    _load_done.setSize({_bar_size.x * percent, _bar_size.y});
}

} // namespace visual
} // namespace gui
