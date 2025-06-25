/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Hud.hpp
*/

#ifndef HUD_HPP_
    #define HUD_HPP_

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
    Drawable bg;
};

class Hud {
    public:
        Hud() = default;
        ~Hud() = default;

        void display(sf::RenderTarget& target, const sf::Clock& clock);
        void event(const sf::Event&);
        
        void changeStatus(HudType_e);
        void changeTrantorInfo(std::shared_ptr<Trantorian>);
        void changeTileInfo(std::shared_ptr<Tile>);

    private:
        float _last_time = 0;
        HudType_e _status = NO_INFO;
        HudInfos _infos;
        HudDisplay _display;
        void updateInfo(void);

        std::shared_ptr<Trantorian> _trantorian = nullptr;
        std::shared_ptr<Tile> _tile = nullptr;

};

} // namespace visual
} // namespace gui


#endif
