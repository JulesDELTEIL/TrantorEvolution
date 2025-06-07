/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.hpp
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_

    #include <vector>

    #include "IScene.hpp"
    #include "ILayer.hpp"

namespace gui {
namespace visual {

class AScene : public IScene {
    public:
        AScene() = default;
        ~AScene() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&) override;

    private:
        std::vector<ILayer> _layers;

};

} // visual
} // gui

#endif
