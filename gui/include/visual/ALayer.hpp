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

    #include "visual/ILayer.hpp"
    #include "visual/IDrawable.hpp"

namespace gui {
namespace visual {

class ALayer : public ILayer {
    public:
        ALayer() = default;
        ~ALayer() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&) override;

    private:
        std::vector<std::unique_ptr<IDrawable>> _drawables;

};

} // visual
} // gui

#endif
