/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IScene.hpp
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>
    #include <SFML/Window/Event.hpp>

    #include "core/Engine.hpp"
    #include "network/events.hpp"

namespace gui {
namespace visual {

class IScene {
    public:
        virtual void display(sf::RenderTarget&) = 0;
        virtual void event(const core::Engine&, const network::NetEventPack&) = 0;
    
        virtual sf::View getView(void) = 0;
        virtual sf::Vector2f getViewPos(void) const = 0;
        virtual void zoom(float) = 0;
        virtual void move(const sf::Vector2f&) = 0;
        virtual void move(float, float) = 0;

    private:

};

} // visual
} // gui

#endif