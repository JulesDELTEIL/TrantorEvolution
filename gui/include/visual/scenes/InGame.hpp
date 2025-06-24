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

    #include "visual/interfaces/AScene.hpp"
    #include "network/Client.hpp"

namespace gui {
namespace visual {

class InGame : public AScene {
    public:
        InGame(std::reference_wrapper<network::Client> client);
        ~InGame() = default;

        void display(sf::RenderTarget&) override;
        void event(const sf::Event&, const network::NetEventPack&) override;

    private:

};

} // visual
} // gui

#endif
