/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Background.cpp
*/

#include "visual/entities/Background.hpp"

namespace gui {
namespace visual {

Background::Background() : _waterfall_anim(std::ref(_waterfall))
{
    _background.texture.loadFromFile(BACKGROUND_PATH);
    _background.sprite.setTexture(_background.texture);
    _background.sprite.setPosition(0, 0);
    _waterfall.texture.loadFromFile(WATERFALL_PATH);
    _waterfall.sprite.setTexture(_waterfall.texture);
    _waterfall_anim.addAnimation(WATERFALL_ANIM);
    _waterfall_anim.animate();
}
    
void Background::drawBackground(sf::RenderTarget& render)
{
    render.draw(_background.sprite);
}

void Background::drawWaterfall(sf::RenderTarget& render, const sf::Vector2i& map_size)
{
    sf::Vector2f pos;

    _waterfall_anim.animate();
    _waterfall.sprite.setScale(1, 1);
    int y = map_size.y;
    for (int x = 0; x <= map_size.x + 1; ++x) {
        pos = MAP_POS(CENTER_MAP(map_size.y), x, y);
        pos.y -= 24.0f;
        _waterfall.sprite.setPosition(pos);
        render.draw(_waterfall.sprite);
    }
    _waterfall.sprite.setScale(-1, 1);
    int x = map_size.x;
    for (int y = 0; y <= map_size.y + 1; ++y) {
        pos = MAP_POS(CENTER_MAP(map_size.y), x, y);
        pos.y -= 24.0f;
        _waterfall.sprite.setPosition(pos);
        render.draw(_waterfall.sprite);
    }
}

} // namespace visual
} // namespace gui
