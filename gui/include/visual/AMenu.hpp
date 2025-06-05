/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AMenu.hpp
*/

#ifndef AMENU_HPP_
    #define AMENU_HPP_

    #include <vector>

    #include "IMenu.hpp"
    #include "ILayer.hpp"

namespace gui {
namespace visual {

enum MenuType_e {
    MAIN,
    LOBBY,
    IN_GAME,
};

class AMenu : public IMenu {
    public:
        AMenu() = default;
        ~AMenu() = default;

        void display(void) const override;
        void event(const sf::Event&) override;

    private:
        std::vector<ILayer> _layers;

};

} // visual
} // gui

#endif
