/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** InGame.hpp
*/

#ifndef INGAME_HPP_
    #define INGAME_HPP_

    #include <string>
    #include <vector>

    #include <visual/interfaces/AScene.hpp>

namespace gui {
namespace visual {

class InGame : public AScene {
    public:
        InGame();
        ~InGame() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&, const network::NetEventPack&) override;

    private:
        void writeTeams(const std::string&);
        std::vector<std::string> _teams;

};

} // visual
} // gui

#endif
