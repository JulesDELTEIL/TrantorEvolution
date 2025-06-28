/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Hud.hpp
*/

#ifndef HUD_HPP_
    #define HUD_HPP_

    #include <SFML/Graphics/Text.hpp>
    #include <SFML/Window/Event.hpp>
    #include <unordered_map>

    #include "map_tools.h"
    #include "core/Engine.hpp"
    #include "visual/Drawable.hpp"
    #include "visual/Text.hpp"
    #include "network/events.hpp"
    #include "visual/visual.hpp"
    #include "Teams.hpp"

    #include "visual/entities/Trantorian.hpp"
    #include "visual/entities/Tile.hpp"

namespace gui {
namespace visual {

    #define UPDATE_INFO 800.0f
    #define HUD_FONT "assets/hud/hud_font.ttf"
    
    #define TILE_HUD_TEXTURE "assets/hud/hud_bg.png"
    #define TILE_HUD_SCALE 1.6f
    #define TILE_HUD_MARGIN 10.0f
    #define TILE_RESOURCES_TEXTURE "assets/hud/resources.png"
    #define TILE_FONT_SIZE 12
    #define TILE_BIOME_FSIZE 16
    #define TILE_BIOME_POS_FACTOR sf::Vector2f(-10.0f, -30.0f);
    #define TILE_COLOR_TEXT sf::Color(93, 60, 0, 255)
    #define TILE_INSIDE_MARGIN 32.0f
    #define TILE_INSIDE_SPLIT 20.0f
    #define HUD_RES_SIZE 10

static const std::map<resource_e, sf::IntRect> HUD_RES_RECT = {
    {FOOD, {0, 0, HUD_RES_SIZE, HUD_RES_SIZE}},
    {WOOD, {10, 0, HUD_RES_SIZE, HUD_RES_SIZE}},
    {STONE, {20, 0, HUD_RES_SIZE, HUD_RES_SIZE}},
    {CLAY, {30, 0, HUD_RES_SIZE, HUD_RES_SIZE}},
    {METAL, {40, 0, HUD_RES_SIZE, HUD_RES_SIZE}},
    {OIL, {50, 0, HUD_RES_SIZE, HUD_RES_SIZE}},
    {ANTI_MATTER, {60, 0, HUD_RES_SIZE, HUD_RES_SIZE}}
};

    #define GLOBAL_HUD_TEXTURE "assets/hud/global_info.png"
    #define GLOBAL_HUD_SCALE 2.0f
    #define GLOBAL_FONT_SIZE 21
    #define GLOBAL_COLOR_TEXT sf::Color(255, 204, 114, 255)
    #define GLOBAL_MARGIN 26.0f
    #define GLOBAL_TEXT_SPLIT(i) (30.0f * i) + 5.0f
    #define G_TIME_POS sf::Vector2f(GLOBAL_MARGIN, GLOBAL_TEXT_SPLIT(1))
    #define G_MAPS_POS sf::Vector2f(GLOBAL_MARGIN, GLOBAL_TEXT_SPLIT(2))
    #define G_NBTE_POS sf::Vector2f(GLOBAL_MARGIN, GLOBAL_TEXT_SPLIT(3))
    #define G_NBTR_POS sf::Vector2f(GLOBAL_MARGIN, GLOBAL_TEXT_SPLIT(4))

    #define UNIT_FOR_DAY 365
    #define DAY_PASS_TIME float(1000.0f * (UNIT_FOR_DAY / this->_time_unit_speed))

    #define DATE_HUD_TEXTURE "assets/hud/date.png"
    #define DATE_HUD_SCALE 2.5f
    #define DATE_FONT_SIZE 24
    #define DATE_HUD_POS sf::Vector2f(WIN_X - 10.0f, 10.0f)
    #define DATE_COLOR_TEXT sf::Color(255, 225, 170, 255)
    #define DATE_NB_POS sf::Vector2f(DATE_HUD_POS.x - 155.0f, 20.0f)

    #define TEAM_HUD_TEXTURE "assets/hud/team.png"
    #define TEAM_HUD_SCALE 3.0f
    #define T_TR_TEXTURE "assets/hud/trantor.png"
    #define T_LVL_TEXTURE "assets/hud/king.png"
    #define T_NAME_SIZE 16
    #define T_POS sf::Vector2f(0.0f, 120.0f)
    #define T_MARGIN sf::Vector2f(0.0f, 80.0f)
    #define T_NAME_POS sf::Vector2f(25.0f, 12.0f)
    #define T_INSIDE_MARGIN sf::Vector2f(0.0f, 25.0f);
    #define T_LEFT_POS sf::Vector2f(25.0f, 35.0f)
    #define T_RIGHT_POS sf::Vector2f(50.0f, 34.2f)

enum HudType_e {
    NO_INFO = -1,
    TILE_INFO,
};

struct TileInfo {
    std::string type;
    sf::Vector2i position;
    ResourceGroup resources;
};

static const std::map<biome_e, std::string> BIOME_NAMES = {
    {SEA, "sea"}, {FOREST, "forest"}, {MOUNTAINS, "mountain"},
    {PLAINS, "plains"}, {BEACH, "beach"}, {EMPTY, "empty"},
};

struct HudDisplay {
    HudDisplay();
    Font font;

    Drawable tile;
    Drawable tile_r;
    Text tile_biome;
    Text tile_rquantity;

    Drawable global;
    Text g_time;
    Text g_map_size;
    Text g_nb_teams;
    Text g_nb_trantors;

    Drawable date;
    Text date_nb;

    Drawable teams;
    Drawable t_trantor;
    Drawable t_lvl;
    Text t_info;
};

class Hud {
    public:
        Hud(std::reference_wrapper<Teams>);
        ~Hud() = default;

        void display(sf::RenderTarget& target, const sf::Clock& clock);
        void event(const sf::Event&, const network::NetEventPack&);
        
        void changeStatus(HudType_e);
        void changeTileInfo(std::shared_ptr<Tile>);
        void updateInfo(void);

    private:
        float _last_time = 0;

        HudDisplay _display;
        void drawHud(sf::RenderTarget&);
    
        float _last_day = 0;
        size_t _time_unit_speed = 1;
        size_t _nb_days = 0;

        size_t _nb_trantors = 0;

        std::reference_wrapper<Teams> _teams;
        std::vector<size_t> _best_lvl;
        void drawTeamsInfos(sf::RenderTarget&);

        HudType_e _status = NO_INFO;
        std::shared_ptr<Tile> _tile = nullptr;
        TileInfo _infos;
        void drawTileInfo(sf::RenderTarget& render);


};

} // namespace visual
} // namespace gui


#endif
