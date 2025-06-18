/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ADrawable.hpp
*/

#ifndef ADRAWABLE_HPP_
    #define ADRAWABLE_HPP_

    #include <SFML/System/Vector2.hpp>

    #include "interfaces/IDrawable.hpp"

namespace ecs {

class ADrawable : public IDrawable {
    public:
        ADrawable(sf::Vector2f entity_origin);
        ~ADrawable() = default;

        void setPosition(const sf::Vector2f&) override;
        sf::Vector2f getPosition(void) const override;
        void setScale(const sf::Vector2f&) override;
        sf::Vector2f getScale(void) const override;
        void changeState(int) override;
        int getState(void) override;

    protected:
        sf::Vector2f _pos;
        sf::Vector2f _scale = {1, 1};
        float _angle = 0.0f;
        int _state = 0;
};

} // ecs

#endif
