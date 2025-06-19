/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultLayer.hpp
*/

#ifndef DEFAULT_LAYER_HPP_
    #define DEFAULT_LAYER_HPP_

    #include "visual/ALayer.hpp"

namespace gui {
namespace visual {

class DefaultLayer : public ALayer {
    public:
        DefaultLayer();
        ~DefaultLayer() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&, const network::NetEventPack&) override;

    private:

};

} // visual
} // gui

#endif
