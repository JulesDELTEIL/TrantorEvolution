/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.hpp
*/

#ifndef LAND_HPP_
    #define LAND_HPP_

    #include <map>

    #include "visual/ALayer.hpp"

    #include "visual/entities/Tile.hpp"
    #include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

    #define TILE_SIZE 32
    #define NB_MAP_ARG 9
    #define CENTER_MAP(map_height) (sf::Vector2f(1280.0f / 2 - (TILE_SIZE / 2), (780.0f - map_height * TILE_SIZE) / 2))
    #define MAP_POS(middle, x, y) (sf::Vector2f((middle.x - (TILE_SIZE / 2) * (x + y)) + (TILE_SIZE * y), middle.y + (8 * (x + y))))

class Land : public ALayer {
    public:
        Land();
        ~Land() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event, const network::NetEventPack&) override;
    

    private:
        void loadTile(const sf::Vector2f&, const network::NetPack&);
        BiomeTypes_e readBiomeType(const network::NetPack& pack);
        void updateTile(const network::NetPack&);
        sf::Vector2f _map_size = {-1, -1};
        bool _map_set = false;

        void addTrantorian(const network::NetPack& pack);

        struct TileInfo {
            std::unique_ptr<Tile> tile;
            std::map<size_t, std::unique_ptr<Trantorian>> trantorians;
            std::vector<std::unique_ptr<ecs::IEntity>> resources;
        };

        std::map<size_t, std::map<size_t, TileInfo>> _tiles;
};

} // visual
} // gui

#endif
