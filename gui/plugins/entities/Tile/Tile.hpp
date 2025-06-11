/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <memory>
    #include <iostream> // test purpose (to delete)

    #include "visual/visual.hpp"
    #include "interfaces/AEntity.hpp"

namespace gui {
namespace visual {

class Tile : public ecs::AEntity {
    public:
        Tile(const sf::Vector2f& pos, BiomeTypes_e type);
        ~Tile() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event) override;

    private:

};

extern "C" {
    std::unique_ptr<ecs::IEntity> tileEntrypoint(double x, double y, int type) {
        return std::make_unique<Tile>(sf::Vector2f(x, y), BiomeTypes_e(type));
    }
}

} // visual
} // gui

#endif
