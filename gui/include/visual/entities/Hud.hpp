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

    #include "visual/Drawable.hpp"
    #include "network/events.hpp"
    #include "visual/visual.hpp"

    #include "visual/entities/Trantorian.hpp"
    #include "visual/entities/Tile.hpp"

namespace gui {
namespace visual {

    #define UPDATE_INFO 500.0f
    
    #define BG_HUD_TEXTURE "assets/hud/hud_bg.jpg"
    #define BG_HUD_SCALE 0.6f

    #define GLOBAL_HUD_TEXTURE "assets/hud/global_info.png"
    #define GLOBAL_HUD_SCALE 2.0f
    #define GLOBAL_FONT_SIZE 21
    #define GLOBAL_COLOR_TEXT sf::Color(255, 204, 114, 255)

    #define GLOBAL_MARGIN 30.0f
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

struct HudInfos {
    std::string type;
    sf::Vector2i position;
    ResourceGroup resources;
};

struct HudDisplay {
    HudDisplay();
    void move(const sf::Vector2f& pos);
    sf::Font font;
    Drawable bg;
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
        void changeTrantorInfo(std::shared_ptr<Trantorian>);
        void changeTileInfo(std::shared_ptr<Tile>);

    private:
        float _last_time = 0;
        HudType_e _status = NO_INFO;
        HudInfos _infos;
        HudDisplay _display;
        void updateInfo(void);

        size_t _nb_trantors = 0;
        size_t _nb_teams = 0;

        std::shared_ptr<Trantorian> _trantorian = nullptr;
        std::shared_ptr<Tile> _tile = nullptr;

};

} // namespace visual
} // namespace gui


#endif
