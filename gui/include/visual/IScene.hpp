/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IScene.hpp
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include <SFML/Window/Event.hpp>

namespace gui {
namespace visual {

enum Scene_e {
    MENU,
    LOBBY,
    IN_GAME,
};

class IScene {
    public:
        virtual void display(void) const = 0;
        virtual void event(const sf::Event&) = 0;
    private:

};

} // visual
} // gui

#endif