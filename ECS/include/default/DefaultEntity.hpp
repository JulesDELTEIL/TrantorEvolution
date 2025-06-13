/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultDrawable.hpp
*/

#ifndef DEFAULT_ENTITY_HPP
    #define DEFAULT_ENTITY_HPP

    #include <memory>

    #include "interfaces/AEntity.hpp"

namespace ecs {
    
class DefaultEntity : public AEntity {
    public:
        DefaultEntity(float x, float y);
        ~DefaultEntity() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event) override;

};

std::unique_ptr<ecs::IEntity> entityEntrypoint(float x, float y) {
    return std::make_unique<DefaultEntity>(x, y);
}

} // namespace ecs

#endif
