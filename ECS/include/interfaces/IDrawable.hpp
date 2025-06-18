/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IDrawable.hpp
*/

#ifndef IDRAWABLE_HPP_
    #define IDRAWABLE_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>
    #include <SFML/Graphics/RenderStates.hpp>

namespace ecs {

class IDrawable {
    public:
        virtual void draw(sf::RenderTarget&) = 0;
        virtual void setPosition(const sf::Vector2f&) = 0;
        virtual sf::Vector2f getPosition(void) const = 0;
        virtual void setScale(const sf::Vector2f&) = 0;
        virtual sf::Vector2f getScale(void) const = 0;
        virtual void changeState(int) = 0;
        virtual int getState(void) = 0;
};

} // ecs

#endif