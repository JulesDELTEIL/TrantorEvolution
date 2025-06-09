/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** GrassTile.hpp
*/

#ifndef GRASS_TILE_HPP_
    #define GRASS_TILE_HPP_

    #include "visual/AObject.hpp"

    #define GRASS_TILE_TEXTURE ""

namespace gui {
namespace visual {

class GrassTile : public AObject {
    public:
        GrassTile(const sf::Vector2f&);
        ~GrassTile() = default;

    private:

};

} // visual
} // gui

#endif
