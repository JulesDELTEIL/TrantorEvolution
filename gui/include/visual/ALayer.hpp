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

namespace gui {
namespace visual {

class ALayer : public ILayer {
    public:
        ALayer() = default;
        ~ALayer() = default;

        void display(void) const override;
        void event(const sf::Event&) override;

    private:
        std::vector<std::unique_ptr<int>> _drawables;

};

} // visual
} // gui

#endif
