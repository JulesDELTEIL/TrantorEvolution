/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ALayer.hpp
*/

#ifndef ALAYER_HPP_
    #define ALAYER_HPP_

    #include <vector>
    #include <memory>

    #include "visual/ILayer.hpp"
    #include "interfaces/IEntity.hpp"

namespace gui {
namespace visual {

class ALayer : public ILayer {
    public:
        ALayer() = default;
        ~ALayer() = default;

        void display(sf::RenderTarget&) const = 0;
        void event(const sf::Event&, const NetPack&) = 0;

    protected:
        std::vector<std::unique_ptr<ecs::IEntity>> _entities;

};

} // visual
} // gui

#endif
