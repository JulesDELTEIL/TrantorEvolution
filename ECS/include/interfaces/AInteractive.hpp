/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AInteractive.hpp
*/

#ifndef AINTERACTIVE
    #define AINTERACTIVE

    #include <SFML/Window/Event.hpp>

namespace ecs {

class AInteractive {
    public:
        AInteractive() = default;
        ~AInteractive() = default;

        virtual void action(const sf::Event&) const = 0;
};

} // ecs

#endif
