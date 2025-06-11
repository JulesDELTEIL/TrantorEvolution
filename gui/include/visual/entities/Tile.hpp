/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include "visual/AEntity.hpp"

namespace gui {
namespace visual {

class Tile : public AEntity {
    public:
        Tile(const sf::Vector2f& pos, BiomeTypes_e type);
        ~Tile() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event) override;

    private:

};

} // visual
} // gui

#endif
