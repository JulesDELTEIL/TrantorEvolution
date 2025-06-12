/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ILayer.hpp
*/

#ifndef ILAYER_HPP_
    #define ILAYER_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>
    #include <SFML/Window/Event.hpp>

namespace gui {
namespace visual {

class ILayer {
    public:
        virtual void display(sf::RenderTarget&) const = 0;
        virtual void event(const sf::Event&) = 0;
    private:

};

} // visual
} // gui

#endif
