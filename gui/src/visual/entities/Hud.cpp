/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Hud.cpp
*/

#include "visual/entities/Hud.hpp"

namespace gui {
namespace visual {

HudDisplay::HudDisplay() :
    font(HUD_FONT),
    tile(TILE_HUD_TEXTURE, TILE_HUD_SCALE), tile_r(TILE_RESOURCES_TEXTURE),
    tile_biome(font, DATE_COLOR_TEXT, TILE_BIOME_FSIZE), tile_rquantity(font, TILE_COLOR_TEXT, TILE_FONT_SIZE),
    global(GLOBAL_HUD_TEXTURE, GLOBAL_HUD_SCALE), g_time(font, GLOBAL_COLOR_TEXT, GLOBAL_FONT_SIZE),
    g_map_size(font, GLOBAL_COLOR_TEXT, GLOBAL_FONT_SIZE), g_nb_teams(font, GLOBAL_COLOR_TEXT, GLOBAL_FONT_SIZE),
    g_nb_trantors(font, GLOBAL_COLOR_TEXT, GLOBAL_FONT_SIZE),
    date(DATE_HUD_TEXTURE, DATE_HUD_SCALE), date_nb(font, DATE_COLOR_TEXT),
    teams(TEAM_HUD_TEXTURE, TEAM_HUD_SCALE), t_trantor(T_TR_TEXTURE),
    t_lvl(T_LVL_TEXTURE), t_info(font, GLOBAL_COLOR_TEXT, T_NAME_SIZE)
{
    tile.sprite.setOrigin(tile.texture.getSize().x / 2, tile.texture.getSize().y + TILE_HUD_MARGIN);
    tile_biome.setFillColor(DATE_COLOR_TEXT);
    tile_biome.setOutlineColor(TILE_COLOR_TEXT);
    tile_biome.setOutlineThickness(0.8f);
    g_time.setPosition(G_TIME_POS);
    g_map_size.setPosition(G_MAPS_POS);
    g_nb_teams.setPosition(G_NBTE_POS);
    g_nb_trantors.setPosition(G_NBTR_POS);
    date.sprite.setOrigin(date.texture.getSize().x, 0.0f);
    date.sprite.setPosition(DATE_HUD_POS);
    date_nb.setPosition(DATE_NB_POS);
    date_nb.setString("Year 0");
    t_info.setOutlineThickness(1.0f);
    t_info.setOutlineColor(TILE_COLOR_TEXT);
}

Hud::Hud(std::reference_wrapper<Teams> teams) : _teams(teams)
{}

void Hud::display(sf::RenderTarget& render, const sf::Clock& clock)
{
    float time_elapsed = clock.getElapsedTime().asMilliseconds();

    if (time_elapsed > _last_day + DAY_PASS_TIME) {
        _nb_days += 1;
        _display.date_nb.setString("Year " + std::to_string(_nb_days));
        _last_day = time_elapsed;
    }
    if (time_elapsed > _last_time + UPDATE_INFO) {
        updateInfo();
        _last_time = time_elapsed;
        _display.g_time.setString("Time:  " + std::to_string(static_cast<int>(clock.getElapsedTime().asSeconds())) + "s");
        _display.g_nb_teams.setString("Team(s):  " + std::to_string(_teams.get().size()));
        _display.g_nb_trantors.setString("Trantorian(s):  " + std::to_string(_nb_trantors));
        for (size_t i = 0; i < _teams.get().size(); ++i) {
            _best_lvl[i] = 0;
            for (const auto& trant : _teams.get()[i].trantorians) {
                if (_best_lvl[i] < trant->lvl)
                    _best_lvl[i] = trant->lvl;
            }
        }
    }
    if (_status == TILE_INFO)
        drawTileInfo(render);
    render.setView(render.getDefaultView());
    drawHud(render);
    drawTeamsInfos(render);
}

void Hud::drawHud(sf::RenderTarget& render)
{
    render.draw(_display.global.sprite);
    render.draw(_display.g_time);
    render.draw(_display.g_map_size);
    render.draw(_display.g_nb_teams);
    render.draw(_display.g_nb_trantors);
    render.draw(_display.date.sprite);
    render.draw(_display.date_nb);
}

void Hud::event(const sf::Event& event, const network::NetEventPack& net_pack)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            _status = NO_INFO;
    }
    switch (static_cast<int>(net_pack.event)) {
        case network::MSIZE:
            _display.g_map_size.setString("World size:  " +
                net_pack.pack[0].getString() + " " + net_pack.pack[1].getString());
            break;
        case network::NEW:
            _nb_trantors += 1;
            break;
        case network::PDEAD:
            _nb_trantors -= 1;
            break;
        case network::TIME: 
            _time_unit_speed = net_pack.pack[0].getSize_t();
            break;
        case network::TIMEM:
            _time_unit_speed = net_pack.pack[0].getSize_t();
            break;
        case network::TEAMS:
            _best_lvl.push_back(0);
            break;
    }
}

void Hud::changeStatus(HudType_e type)
{
    _status = type;
}

void Hud::changeTileInfo(std::shared_ptr<Tile> new_tile)
{
    _tile = new_tile;
}

void Hud::updateInfo(void)
{
    if (_status == TILE_INFO) {
        if (_tile == nullptr) {
            _status = NO_INFO;
            return;
        }
        _infos.resources = _tile->getResources();
        _infos.type = BIOME_NAMES.at(_tile->getBiome());
        _display.tile_biome.setString(_infos.type);
        _display.tile.sprite.setPosition(_tile->getPos());
    }
}

void Hud::drawTileInfo(sf::RenderTarget& render)
{
    sf::Vector2f pos = _display.tile.sprite.getPosition();
    sf::Vector2f biome_pos;
    sf::Vector2f sp_pos;
    int i = 0;

    render.draw(_display.tile.sprite);
    pos.x -= _display.tile.texture.getSize().x / 2 * TILE_HUD_SCALE - TILE_INSIDE_MARGIN;
    pos.y -= _display.tile.texture.getSize().y / 2 * TILE_HUD_SCALE + TILE_INSIDE_MARGIN - 2.0f;
    biome_pos = pos + TILE_BIOME_POS_FACTOR;
    _display.tile_biome.setPosition(biome_pos);
    render.draw(_display.tile_biome);
    for (const auto& res : _infos.resources) {
        pos.x += TILE_INSIDE_SPLIT;
        if (i == NB_RESOURCES / 2) {
            pos.x -= (TILE_INSIDE_SPLIT + 2.0f) * i;
            pos.y += 15.0f;
        }
        sp_pos = pos;
        sp_pos.x -= 13.0f;
        sp_pos.y += 1.0f;
        _display.tile_r.sprite.setTextureRect(HUD_RES_RECT.at(res.first));
        _display.tile_r.sprite.setPosition(sp_pos);
        _display.tile_rquantity.setString(std::to_string(res.second));
        _display.tile_rquantity.setPosition(pos);
        render.draw(_display.tile_r.sprite);
        render.draw(_display.tile_rquantity);
        i += 1;
    }
}

void Hud::drawTeamsInfos(sf::RenderTarget& render)
{
    sf::Vector2f pos = T_POS;

    for (size_t i = 0; i < _teams.get().size(); ++i) {
        pos += T_MARGIN;
        _display.teams.sprite.setColor(_teams.get()[i].color);
        _display.teams.sprite.setPosition(pos);
        render.draw(_display.teams.sprite);
        _display.t_info.setPosition(pos + T_NAME_POS);
        _display.t_info.setString(_teams.get()[i].name);
        render.draw(_display.t_info);
        
        _display.t_trantor.sprite.setColor(_teams.get()[i].color);
        _display.t_trantor.sprite.setPosition(pos + T_LEFT_POS);
        render.draw(_display.t_trantor.sprite);
        _display.t_info.setPosition(pos + T_RIGHT_POS);
        _display.t_info.setString(std::to_string(_teams.get()[i].trantorians.size()));
        render.draw(_display.t_info);
        
        pos += T_INSIDE_MARGIN;
        _display.t_lvl.sprite.setPosition(pos + T_LEFT_POS);
        render.draw(_display.t_lvl.sprite);
        _display.t_info.setPosition(pos + T_RIGHT_POS);
        _display.t_info.setString(std::to_string(_best_lvl[i]));
        render.draw(_display.t_info);

    }
}

} // namespace visual
} // namespace gui
