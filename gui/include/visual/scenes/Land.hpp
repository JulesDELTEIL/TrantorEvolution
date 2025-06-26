/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.hpp
*/

#ifndef LAND_HPP_
    #define LAND_HPP_

    #include <map>
    #include <thread>
    #include <SFML/System/Clock.hpp>

    #include "visual/AScene.hpp"

    #include "map_tools.h"
    #include "core/Engine.hpp"
    #include "network/Client.hpp"
    #include "visual/entities/Background.hpp"
    #include "visual/entities/Hud.hpp"
    #include "visual/entities/Tile.hpp"
    #include "visual/entities/Trantorian.hpp"
    #include "visual/entities/ResourceNode.hpp"
    #include "visual/entities/IncantationObject.hpp"

namespace gui {
namespace visual {

    #define NB_MAP_ARG 9
    #define CENTER_MAP(map_height) (sf::Vector2f(VIEW_WIDTH, (VIEW_HEIGHT * 2 - map_height * TILE_SIZE) / 2))
    #define MAP_POS(middle, x, y) (sf::Vector2f((middle.x - (TILE_SIZE / 2) * (x + y)) + (TILE_SIZE * y), middle.y + (24 * (x + y))))

    #define ACT_TIME(x) float((x / this->_time_unit_speed) * 1000)

struct ClearTile {
    float time;
    resource_e type;
    sf::Vector2i tile;
};

class Land : public AScene {
    public:
        Land();
        ~Land() = default;

        void display(sf::RenderTarget& render) override;
        void event(const core::Engine&, const network::NetEventPack&) override;

    private:
        sf::Clock _clock;
        size_t _time_unit_speed = 4;

        void viewEvent(const sf::Event&);

        void loadTile(const network::NetPack&);
        biome_e readBiomeType(const network::NetPack& pack);
        void updateTile(const network::NetPack&);
        Drawable _tile;
        sf::Vector2f _map_size = {-1, -1};
        bool _map_set = false;

        void clearResources(void);
        std::vector<ClearTile> _clear_resources;

        void addTrantorian(const network::NetPack& pack);
        void removeTrantorian(const network::NetPack& pack);
        void trantorCollect(const network::NetPack& pack);
        void trantorStartIncantation(const network::NetPack& pack);
        void trantorEndIncantation(const network::NetPack& pack);
        void posTrantorian(const network::NetPack& pack);

        Background _backgroud;

        Hud _hud;
        void checkHudEvent(const core::Engine& engine, const network::NetEventPack& net_pack);
        bool hitTrantor(const sf::Vector2f&);
        bool hitTile(const sf::Vector2f&);

        struct TileInfo {
            std::shared_ptr<Tile> tile;
            std::map<size_t, std::shared_ptr<Trantorian>> trantorians;
            std::map<resource_e, std::shared_ptr<ResourceNode>> resources;
            std::shared_ptr<IncantationObject> incantation_objects;
        };

        std::map<size_t, std::map<size_t, TileInfo>> _tiles;
        std::map<size_t, std::shared_ptr<Trantorian>> _trantorians;
};

} // visual
} // gui

#endif
