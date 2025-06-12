/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IDrawable.hpp
*/

#ifndef IDRAWABLE_HPP_
    #define IDRAWABLE_HPP_

    #include <SFML/Graphics/Drawable.hpp>

namespace ecs {

class IDrawable : public sf::Drawable {
    public:
        virtual void setPosition(const sf::Vector2f&) = 0;
        virtual sf::Vector2f getPosition(void) const = 0;
        virtual void setRotation(float) = 0;
        virtual float getRotation(void) const = 0;

};

} // ecs

#endif