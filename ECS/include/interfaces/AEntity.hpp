/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AEntity.hpp
*/

#ifndef AENTITY_HPP_
    #define AENTITY_HPP_

    #include <map>
    #include <memory>

    #include "interfaces/IEntity.hpp"
    #include "interfaces/IDrawable.hpp"
    #include "interfaces/AInteractive.hpp"

namespace ecs {

class AEntity : public IEntity{
    public:
        AEntity(const sf::Vector2f& pos);

        void display(sf::RenderTarget&) const = 0;
        void event(const sf::Event&) = 0;

        void updatePosition(const sf::Vector2f&) override;
        void zoom(const sf::Vector2f&) override;

    protected:
        sf::Vector2f _origin;
        std::map<std::string, std::unique_ptr<IDrawable>> _drawables;
        std::map<std::string, std::unique_ptr<AInteractive>> _interactives;
};

} // ecs

#endif
