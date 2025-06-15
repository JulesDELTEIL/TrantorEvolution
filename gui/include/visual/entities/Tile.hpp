/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <memory>

    #include "visual/visual.hpp"
    #include "interfaces/AEntity.hpp"

namespace gui {
namespace visual {

    #define RES_MAX_X 25
    #define RES_MIN_X 8
    #define RES_MAX_Y 9
    #define RES_MIN_Y 4

static const int RES_RANGE_X = RES_MAX_X - RES_MIN_X + 1;
static const int RES_RANGE_Y = RES_MAX_Y - RES_MIN_Y + 1;

class Tile : public ecs::AEntity {
    public:
        Tile(const sf::Vector2f& pos, BiomeTypes_e type,
            const std::vector<ResourceType_e>&);
        ~Tile() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event) override;

    private:

};

} // visual
} // gui

#endif
