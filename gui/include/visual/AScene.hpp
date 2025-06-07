/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.hpp
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_

    #include <vector>
    #include <memory>

    #include "visual/IScene.hpp"
    #include "visual/ALayer.hpp"

namespace gui {
namespace visual {

class AScene : public IScene {
    public:
        AScene() = default;
        ~AScene() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&) override;

    protected:
        std::vector<std::unique_ptr<ILayer>> _layers;

};

} // visual
} // gui

#endif
