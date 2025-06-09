/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultEntity.hpp
*/

#ifndef DEFAULT_ENTITY_HPP_
    #define DEFAULT_ENTITY_HPP_

    #include "visual/AEntity.hpp"

namespace gui {
namespace visual {

class DefaultEntity : public AEntity {
    public:
        DefaultEntity();
        ~DefaultEntity() = default;

        void display(sf::RenderTarget&) const override;
        void event(const sf::Event&) override;

};

} // visual
} // gui

#endif
