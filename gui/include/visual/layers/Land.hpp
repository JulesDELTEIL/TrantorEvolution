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
