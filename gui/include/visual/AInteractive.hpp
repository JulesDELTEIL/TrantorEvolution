/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AInteractive.hpp
*/

#ifndef AINTERACTIVE
    #define AINTERACTIVE

namespace gui {
namespace visual {

class AInteractive {
    public:
        AInteractive() = default;
        ~AInteractive() = default;

        virtual void action(sf::Event&) const = 0;
};


} // gui
} // visual

#endif
