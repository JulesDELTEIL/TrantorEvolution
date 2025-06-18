/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ALayer.hpp
*/

#ifndef ALAYER_HPP_
    #define ALAYER_HPP_

    #include <vector>
    #include <memory>

    #include "visual/interfaces/ILayer.hpp"

namespace gui {
namespace visual {

class ALayer : public ILayer {
    public:
        ALayer() = default;
        ~ALayer() = default;

        void display(sf::RenderTarget&) const = 0;
        void event(const sf::Event&, const network::NetEventPack&) = 0;

    protected:

};

} // visual
} // gui

#endif
