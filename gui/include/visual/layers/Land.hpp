/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.hpp
*/

#ifndef LAND_HPP_
    #define LAND_HPP_

    #include <map>
    #include <SFML/System/Clock.hpp>

    #include "visual/interfaces/ALayer.hpp"

    #include "visual/entities/Tile.hpp"
    #include "visual/entities/Trantorian.hpp"
    #include "visual/entities/ResourceNode.hpp"

namespace gui {
namespace visual {

    #define TILE_SIZE 32
    #define NB_MAP_ARG 9
    #define CENTER_MAP(map_height) (sf::Vector2f(1280.0f / 2, (780.0f - map_height * TILE_SIZE) / 2))
    #define MAP_POS(middle, x, y) (sf::Vector2f((middle.x - (TILE_SIZE / 2) * (x + y)) + (TILE_SIZE * y), middle.y + (8 * (x + y))))

    #define ACT_TIME(x) float((x / this->_time_unit_speed) * 1000)

struct ClearTile {
    float time;
    sf::Vector2i tile;
};

class Land : public ALayer {
    public:
        Land();
        ~Land() = default;

        void display(sf::RenderTarget& render) override;
        void event(const sf::Event& event, const network::NetEventPack&) override;
    

    private:
        sf::Clock _clock;
        size_t _time_unit_speed = 4;

        void loadTile(const network::NetPack&);
        BiomeTypes_e readBiomeType(const network::NetPack& pack);
        void updateTile(const network::NetPack&);
        sf::Vector2f _map_size = {-1, -1};
        bool _map_set = false;

        void addResourceInTile(int, int, const sf::Vector2f&, ResourceType_e, size_t);
        void clearResources(void);
        std::vector<ClearTile> _clear_resources;

        void addTrantorian(const network::NetPack& pack);
        void posTrantorian(const network::NetPack& pack);

        struct TileInfo {
            std::unique_ptr<Tile> tile;
            std::map<size_t, std::shared_ptr<Trantorian>> trantorians;
            std::vector<std::shared_ptr<ResourceNode>> resources;
        };

        std::map<size_t, std::map<size_t, TileInfo>> _tiles;
        std::map<size_t, std::shared_ptr<Trantorian>> _trantorians;
};

} // visual
} // gui

#endif
