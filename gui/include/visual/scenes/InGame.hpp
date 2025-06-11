/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** InGame.hpp
*/

#ifndef INGAME_HPP_
    #define INGAME_HPP_

    #include <visual/AScene.hpp>

namespace gui {
namespace visual {

class InGame : public AScene {
    public:
        InGame();
        ~InGame() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&) override;

    private:

};

} // visual
} // gui

#endif
