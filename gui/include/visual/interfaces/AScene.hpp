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

    #include "visual/interfaces/IScene.hpp"
    #include "visual/interfaces/ALayer.hpp"

namespace gui {
namespace visual {

class AScene : public IScene {
    public:
        AScene(const sf::FloatRect&);
        ~AScene() = default;

        void display(sf::RenderTarget&) = 0;
        void event(const sf::Event&, const network::NetEventPack&) = 0;

        sf::View getView(void) override;
        void zoom(float) override;
        void move(const sf::Vector2f&) override;
        void move(float, float) override;

    protected:
        sf::View _camera;
        std::vector<std::unique_ptr<ILayer>> _layers;

};

} // visual
} // gui

#endif
