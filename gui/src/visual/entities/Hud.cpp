/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Hud.cpp
*/

#include <iostream> // test purpose (to delete)

#include "visual/entities/Hud.hpp"

namespace gui {
namespace visual {

HudDisplay::HudDisplay()
{   
    bg.texture.loadFromFile(BG_HUD_TEXTURE);
    bg.sprite.setTexture(bg.texture);
    bg.sprite.setScale(BG_HUD_SCALE, BG_HUD_SCALE);
    bg.sprite.setOrigin(bg.texture.getSize().x / 2, bg.texture.getSize().y);
}

void HudDisplay::move(const sf::Vector2f& pos)
{
    bg.sprite.setPosition(pos);
}

void Hud::display(sf::RenderTarget& target, const sf::Clock& clock)
{
    if (clock.getElapsedTime().asMilliseconds() > _last_time + UPDATE_INFO)
        updateInfo();
    if (_status != NO_INFO) {
        target.draw(_display.bg.sprite);
    }
}

void Hud::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            _status = NO_INFO;
    }
}

void Hud::changeStatus(HudType_e type)
{
    _status = type;
}

void Hud::changeTrantorInfo(std::shared_ptr<Trantorian> new_trantor)
{
    _trantorian = new_trantor;
}

void Hud::changeTileInfo(std::shared_ptr<Tile> new_tile)
{
    _tile = new_tile;
}

void Hud::updateInfo(void)
{
    switch (static_cast<int>(_status)) {
        case TRANTOR_INFO:
            if (_trantorian == nullptr) {
                _status = NO_INFO;
                return;
            }
            _infos.position = _trantorian->map_pos;
            _infos.resources = _trantorian->getInventory();
            _display.move(_trantorian->actual_pos);
            break;
        case TILE_INFO:
            if (_tile == nullptr) {
                _status = NO_INFO;
                return;
            }
            _infos.resources = _tile->getResources();
            _display.move(_tile->getPos());
            break;
    }
}

} // namespace visual
} // namespace gui
