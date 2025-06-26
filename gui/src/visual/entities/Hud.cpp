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
    font.loadFromFile(HUD_FONT);
    bg.texture.loadFromFile(BG_HUD_TEXTURE);
    bg.sprite.setTexture(bg.texture);
    bg.sprite.setScale(BG_HUD_SCALE, BG_HUD_SCALE);
    bg.sprite.setOrigin(bg.texture.getSize().x / 2, bg.texture.getSize().y);
    global.texture.loadFromFile(GLOBAL_HUD_TEXTURE);
    global.sprite.setTexture(global.texture);
    global.sprite.setScale(GLOBAL_HUD_SCALE, GLOBAL_HUD_SCALE);
    g_time.setFont(font);
    g_time.setFillColor(GLOBAL_COLOR_TEXT);
    g_time.setCharacterSize(GLOBAL_FONT_SIZE);
    g_time.setPosition(G_TIME_POS);
    g_map_size.setFont(font);
    g_map_size.setFillColor(GLOBAL_COLOR_TEXT);
    g_map_size.setCharacterSize(GLOBAL_FONT_SIZE);
    g_map_size.setPosition(G_MAPS_POS);
    g_nb_teams.setFont(font);
    g_nb_teams.setFillColor(GLOBAL_COLOR_TEXT);
    g_nb_teams.setCharacterSize(GLOBAL_FONT_SIZE);
    g_nb_teams.setPosition(G_NBTE_POS);
    g_nb_trantors.setFont(font);
    g_nb_trantors.setFillColor(GLOBAL_COLOR_TEXT);
    g_nb_trantors.setCharacterSize(GLOBAL_FONT_SIZE);
    g_nb_trantors.setPosition(G_NBTR_POS);
}

void HudDisplay::move(const sf::Vector2f& pos)
{
    bg.sprite.setPosition(pos);
}

void Hud::display(sf::RenderTarget& render, const sf::Clock& clock)
{
    if (clock.getElapsedTime().asMilliseconds() > _last_time + UPDATE_INFO) {
        updateInfo();
        _last_time = clock.getElapsedTime().asMilliseconds();
        _display.g_time.setString("Time:  " + std::to_string(static_cast<int>(clock.getElapsedTime().asSeconds())) + "s");
        _display.g_nb_teams.setString("Team(s):  " + std::to_string(_nb_teams.size()));
        _display.g_nb_trantors.setString("Trantorian(s):  " + std::to_string(_nb_trantors));
    }
    if (_status != NO_INFO)
        render.draw(_display.bg.sprite);
    render.setView(render.getDefaultView());
    render.draw(_display.global.sprite);
    render.draw(_display.g_time);
    render.draw(_display.g_map_size);
    render.draw(_display.g_nb_teams);
    render.draw(_display.g_nb_trantors);
}

void Hud::event(const sf::Event& event, const network::NetEventPack& net_pack)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            _status = NO_INFO;
    }
    switch (static_cast<int>(net_pack.event)) {
        case network::MSIZE:
            _display.g_map_size.setString("Map size:  " +
                net_pack.pack[0].getString() + " " + net_pack.pack[1].getString());
            break;
        case network::NEW:
            _nb_trantors += 1;
            break;
        case network::PDEAD:
            _nb_trantors -= 1;
            break;
        case network::TEAMS:
            _nb_teams[net_pack.pack[0].getString()] = 1;
            break;
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
