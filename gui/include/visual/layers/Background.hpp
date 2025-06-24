/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Background.hpp
*/

#ifndef BACKGROUND_HPP_
    #define BACKGROUND_HPP_

    #include "visual/interfaces/ALayer.hpp"

    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

    #define BACKGROUND_PATH "assets/background.png"

class Background : public ALayer {
    public:
        Background();
        ~Background() = default;
    
        void display(sf::RenderTarget& render) override;
        void event(const sf::Event&, const network::NetEventPack&) override;

    private:
        Drawable _background;

};
    
} // namespace visual
} // namespace gui

#endif
