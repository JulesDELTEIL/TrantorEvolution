/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Movement.hpp
*/

#ifndef MOVEMENT_HPP_
    #define MOVEMENT_HPP_

    #include <SFML/System/Clock.hpp>
    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

class Movement {
    public:
        Movement(std::reference_wrapper<Drawable>);
        ~Movement() = default;

        void changeDestination(const sf::Vector2f&, float);
        void move(void);

    private:
        std::reference_wrapper<Drawable> _drawable;
        sf::Clock _clock;
        float _time;
        float _elapsed;
        sf::Vector2f _to_go;
        sf::Vector2f _direction;
};

} // visual
} // gui

#endif

