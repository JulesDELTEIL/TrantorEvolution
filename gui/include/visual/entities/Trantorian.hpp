/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.hpp
*/

#ifndef TRANTORIAN_HPP_
    #define TRANTORIAN_HPP_

    #include "interfaces/AEntity.hpp"

namespace gui {
namespace visual {

class Trantorian : public ecs::AEntity {
    public:
        Trantorian(const sf::Vector2f& pos);
        ~Trantorian() = default;

        void display(sf::RenderTarget& render) const override;
        void event(int event) override;
    private:

};

} // visual
} // gui

#endif
