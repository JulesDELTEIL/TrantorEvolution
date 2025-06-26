/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Background.hpp
*/

#ifndef BACKGROUND_HPP_
    #define BACKGROUND_HPP_

    #include <SFML/Window/Event.hpp>
    #include <SFML/Graphics/RenderTarget.hpp>

    #include "network/events.hpp"
    #include "core/Engine.hpp"
    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

    #define BACKGROUND_PATH "assets/background.png"

class Background {
    public:
        Background();
        ~Background() = default;
    
        void display(sf::RenderTarget& render);
        void event(const core::Engine&, const network::NetEventPack&);

    private:
        Drawable _background;

};
    
} // namespace visual
} // namespace gui

#endif
