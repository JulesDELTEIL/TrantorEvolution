/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** IncantationObject.hpp
*/

#ifndef INCANTATION_OBJECT_HPP_
    #define INCANTATION_OBJECT_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>

    #include "visual/Drawable.hpp"

    #define INCANTATION_RES_MAX_X 24
    #define INCANTATION_RES_MIN_X -24
    #define INCANTATION_RES_MAX_Y 39
    #define INCANTATION_RES_MIN_Y 9

static const int INCANTATION_RES_RANGE_X = INCANTATION_RES_MAX_X - INCANTATION_RES_MIN_X + 1;
static const int INCANTATION_RES_RANGE_Y = INCANTATION_RES_MAX_Y - INCANTATION_RES_MIN_Y + 1;

static const std::string PEDESTAL_TEXTURE("assets/object/Pedestal-Sheet.png");

namespace gui {
namespace visual {

static const sf::IntRect PEDESTAL_RECT(0, 0, 50, 37);

class IncantationObject {
    public:
        IncantationObject(const sf::Vector2f&);
        ~IncantationObject() = default;

        void draw(sf::RenderTarget&);
        sf::Vector2f getIncantationPosition(void);
    private:
        Drawable _pedestal;
        bool _left_side;
};
    
} // visual
} // gui

#endif