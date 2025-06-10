/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IDrawable.hpp
*/

#ifndef IDRAWABLE_HPP_
    #define IDRAWABLE_HPP_

    #include <SFML/Graphics/Drawable.hpp>

    #include "visual/visual.hpp"

namespace gui {
namespace visual {

class IDrawable : public sf::Drawable {
    public:
        virtual VisualType_e getId(void) = 0;

        virtual void setPosition(const sf::Vector2f&) = 0;
        virtual sf::Vector2f getPosition(void) const = 0;
        virtual void setRotation(float) = 0;
        virtual float getRotation(void) const = 0;

};

} // visual
} // gui

#endif