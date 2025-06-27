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
    #include "visual/Drawable.hpp"
    #include "network/events.hpp"
    #include "visual/visual.hpp"

    #include "visual/entities/Trantorian.hpp"
    #include "visual/entities/Tile.hpp"

namespace gui {
namespace visual {

    #define UPDATE_INFO 500.0f
    
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

    #define HUD_FONT "assets/hud/hud_font.ttf"

enum HudType_e {
    NO_INFO = -1,
    TRANTOR_INFO,
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
    sf::Font font;
    Drawable tile;
    Drawable tile_r;
    sf::Text tile_biome;
    sf::Text tile_rquantity;
    Drawable global;
    sf::Text g_time;
    sf::Text g_map_size;
    sf::Text g_nb_trantors;
    sf::Text g_nb_teams;
};

class Hud {
    public:
        Hud() = default;
        ~Hud() = default;

        void display(sf::RenderTarget& target, const sf::Clock& clock);
        void event(const sf::Event&, const network::NetEventPack&);
        
        void changeStatus(HudType_e);
        void changeTileInfo(std::shared_ptr<Tile>);
        void updateInfo(void);

    private:
        float _last_time = 0;
        HudType_e _status = NO_INFO;
        HudDisplay _display;

        size_t _nb_trantors = 0;
        std::unordered_map<std::string, int> _nb_teams;

        void drawTileInfo(sf::RenderTarget& render);

        std::shared_ptr<Tile> _tile = nullptr;
        TileInfo _infos;

};

} // namespace visual
} // namespace gui


#endif
