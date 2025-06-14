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
        Land(const std::vector<int>&);
        ~Land() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event) override;
    
    private:
        void loadMap(const std::vector<int>&);
        std::vector<std::unique_ptr<Tile>> _tiles;
};

} // visual
} // gui

#endif
