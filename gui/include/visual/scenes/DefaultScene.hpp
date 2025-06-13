/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultScene.hpp
*/

#ifndef DEFAULT_SCENE_HPP_
    #define DEFAULT_SCENE_HPP_

    #include "visual/AScene.hpp"

namespace gui {
namespace visual {

class DefaultScene : public AScene {
    public:
        DefaultScene();
        ~DefaultScene() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&) override;

    private:

};

} // visual
} // gui

#endif
