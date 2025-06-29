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
    #include "Teams.hpp"
    #include "core/Engine.hpp"
    #include "network/Client.hpp"
    #include "audio/SoundManage.hpp"
    #include "visual/entities/Background.hpp"
    #include "visual/entities/Hud.hpp"
    #include "visual/entities/Tile.hpp"
    #include "visual/entities/ResourceNode.hpp"
    #include "visual/entities/IncantationObject.hpp"
    #include "visual/entities/Egg.hpp"
    #include "visual/entities/LoadingScreen.hpp"

namespace gui {
namespace visual {

    #define NB_MAP_ARG 9

    #define MOV_FACTOR 20
    #define TIME_TO_FIND 3000 // as ms
    #define ACT_TIME(x) float((x / this->_time_unit_speed) * 1000)

struct ClearTile {
    float time;
    resource_e type;
    sf::Vector2i tile;
};

class Land : public AScene {
    public:
        Land(std::reference_wrapper<network::Client>);
        ~Land();

        void display(sf::RenderTarget& render) override;
        void event(const core::Engine&, const network::NetEventPack&) override;
        biome_e getCenterTileType(const sf::Vector2f &map_center);
        void updateAmbiantSound();

    private:
        std::reference_wrapper<network::Client> _client; 
        std::thread _net;
        bool _net_running = false;
        void askResources(void);

        size_t _time_unit_speed = 4;

        void viewEvent(const sf::Event&);

        void drawEdge(sf::RenderTarget& render, int bottom);
        void addTile(const network::NetPack&);
        void updateTile(const network::NetPack&);
        Drawable _tile;
        sf::Vector2i _map_size = {-1, -1};
        bool _map_set = false;

        LoadingScreen _loading;
        void loadingEvents(const network::NetEventPack&);

        void clearResources(void);
        std::vector<ClearTile> _clear_resources;

        void addTrantorian(const network::NetPack& pack);
        void removeTrantorian(const network::NetPack& pack);
        void trantorCollect(const network::NetPack& pack);
        void trantorStartIncantation(const network::NetPack& pack);
        void trantorEndIncantation(const network::NetPack& pack);
        void trantorLayingAnEgg(const network::NetPack& pack);
        void trantorLaidAnEgg(const network::NetPack& pack);
        void eggHatching(const network::NetPack& pack);
        void posTrantorian(const network::NetPack& pack);
        void updateInventory(const network::NetPack& pack);

        Background _backgroud;
    
        SoundManage biome_song;
        biome_e last_song_biome;

        Hud _hud;
        void checkHudEvent(const core::Engine& engine, const network::NetEventPack& net_pack);
        bool hitTile(const sf::Vector2f&);
        int _selected_tr = -1;

        struct TileInfo {
            std::shared_ptr<Tile> tile;
            std::map<size_t, std::shared_ptr<Trantorian>> trantorians;
            std::map<resource_e, std::shared_ptr<ResourceNode>> resources;
            std::shared_ptr<IncantationObject> incantation_objects;
        };

        std::map<size_t, std::map<size_t, TileInfo>> _tiles;
        std::map<size_t, std::shared_ptr<Trantorian>> _trantorians;
        std::map<size_t, std::shared_ptr<Egg>> _eggs;
        Teams _teams;
};

} // visual
} // gui

#endif
