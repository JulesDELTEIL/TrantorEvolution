/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IEntity.hpp
*/

#ifndef IENTITY_HPP_
    #define IENTITY_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>
    #include <SFML/Window/Event.hpp>

namespace ecs {

class IEntity {
    public:
        virtual void display(sf::RenderTarget&) const = 0;
        virtual void event(int) = 0;

        virtual void updatePosition(const sf::Vector2f&) = 0;
};

} // ecs

#endif
