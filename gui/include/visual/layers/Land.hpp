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

namespace gui {
namespace visual {

    #define TILE_SIZE 32
    #define CENTER_MAP(map_height) (sf::Vector2f(1280.0f / 2 - (TILE_SIZE / 2), (780.0f - map_height * TILE_SIZE) / 2))

class Land : public ALayer {
    public:
        Land() = default;
        ~Land() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event) override;
    
        void loadMap(const sf::Vector2f&,
            const std::vector<std::vector<TileInfo_s>>&);
    private:
        uint8_t convertResource(const std::array<bool, NB_RESOURCES>&);
        std::vector<std::unique_ptr<Tile>> _tiles;
};

} // visual
} // gui

#endif
