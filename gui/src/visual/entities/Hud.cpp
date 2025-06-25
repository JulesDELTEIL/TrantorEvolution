/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Hud.cpp
*/

#include "visual/entities/Hud.hpp"

namespace gui {
namespace visual {

HudDisplay::HudDisplay()
{
    sf::Texture bg_texture;
    
    bg_texture.loadFromFile(BG_HUD_TEXTURE);
    bg.setTexture(bg_texture);
}

void HudDisplay::move(const sf::Vector2f& pos)
{
    bg.setPosition(pos);
}

void Hud::display(sf::RenderTarget& target, const sf::Clock& clock)
{
    if (clock.getElapsedTime().asMilliseconds() > _last_time + UPDATE_INFO)
        updateInfo();
    if (_status != NO_INFO) {
        target.draw(_display.bg);
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
            if (_trantorian == nullptr)
                _status = NO_INFO;
            _infos.position = _trantorian->map_pos;
            _infos.resources = _trantorian->getInventory();
            _display.move(_trantorian->actual_pos);
            break;
        case TILE_INFO:
            if (_tile == nullptr)
                _status = NO_INFO;
            _infos.resources = _tile->getResources();
            _display.move(_tile->getPos());
            break;
    }
}

} // namespace visual
} // namespace gui
