/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.hpp
*/

#ifndef LAND_HPP_
    #define LAND_HPP_

    #include "visual/ALayer.hpp"

    #include "visual/entities/Tile.hpp"
    #include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

    #define TILE_SIZE 32
    #define CENTER_MAP(map_height) (sf::Vector2f(1280.0f / 2 - (TILE_SIZE / 2), (780.0f - map_height * TILE_SIZE) / 2))
    #define MAP_POS(middle, x, y) (sf::Vector2f((middle.x - (TILE_SIZE / 2) * (x + y)) + (TILE_SIZE * y), middle.y + (8 * (x + y))))

class Land : public ALayer {
    public:
        Land();
        ~Land() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event, const NetPack&) override;
    
        void loadMap(const sf::Vector2f&,
            const std::vector<std::vector<TileInfo_s>>&);
        void addTrantorian(int x, int y);

    private:
        uint8_t convertResource(const std::array<bool, NB_RESOURCES>&);
        std::vector<std::unique_ptr<Tile>> _tiles;

        std::vector<std::unique_ptr<Trantorian>> _trantorians;
};

} // visual
} // gui

#endif
