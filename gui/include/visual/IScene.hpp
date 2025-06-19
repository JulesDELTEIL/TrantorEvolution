/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IScene.hpp
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include <SFML/Graphics/Rect.hpp>
    #include <SFML/Graphics/RenderTarget.hpp>
    #include <SFML/Window/Event.hpp>

    #include "network/events.hpp"

namespace gui {
namespace visual {

class IScene {
    public:
        virtual void display(sf::RenderTarget&) const = 0;
        virtual void event(const sf::Event&, const network::NetEventPack&) = 0;
    
        virtual sf::View getView(void) = 0;
        virtual void zoom(float) = 0;
        virtual void move(const sf::Vector2f&) = 0;
        virtual void move(float, float) = 0;

    private:

};

} // visual
} // gui

#endif