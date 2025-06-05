/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IMenu.hpp
*/

#ifndef IMENU_HPP_
    #define IMENU_HPP_

    #include <SFML/Window/Event.hpp>

namespace gui {
namespace visual {

enum MenuType_e {
    MAIN,
    LOBBY,
    IN_GAME,
};

class IMenu {
    public:
        virtual void display(void) const = 0;
        virtual void event(const sf::Event&) = 0;
    private:

};

} // visual
} // gui

#endif