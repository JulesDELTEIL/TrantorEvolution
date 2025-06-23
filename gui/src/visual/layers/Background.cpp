/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Background.cpp
*/

#include "visual/layers/Background.hpp"

namespace gui {
namespace visual {

Background::Background(const sf::FloatRect& view)
{
    _background.texture.loadFromFile(BACKGROUND_PATH);
    sf::Vector2u size = _background.texture.getSize();
    _background.sprite.setTexture(_background.texture);
    _background.sprite.setPosition(0, 0);
}
    
void Background::display(sf::RenderTarget& render)
{
    render.draw(_background.sprite);
}

void Background::event(const sf::Event& event, const network::NetEventPack&)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::D)
            _background.sprite.move(2.0f, 0);
        if (event.key.code == sf::Keyboard::Q)
            _background.sprite.move(-2.0f, 0);
        if (event.key.code == sf::Keyboard::S)
            _background.sprite.move(0, 2.0f);
        if (event.key.code == sf::Keyboard::Z)
            _background.sprite.move(0, -2.0f);
    }
}

} // namespace visual
} // namespace gui
