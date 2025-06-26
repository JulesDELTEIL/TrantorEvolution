/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Background.cpp
*/

#include "visual/entities/Background.hpp"

namespace gui {
namespace visual {

Background::Background()
{
    _background.texture.loadFromFile(BACKGROUND_PATH);
    _background.sprite.setTexture(_background.texture);
    _background.sprite.setPosition(0, 0);
}
    
void Background::display(sf::RenderTarget& render)
{
    render.draw(_background.sprite);
}

void Background::event(const core::Engine&, const network::NetEventPack&)
{

}

} // namespace visual
} // namespace gui
