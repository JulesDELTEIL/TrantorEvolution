/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Hud.hpp
*/

#ifndef HUD_HPP_
    #define HUD_HPP_

    #include "visual/interfaces/ALayer.hpp"

    #include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

class Hud : public ALayer {
    public:
        Hud() = default;
        ~Hud() = default;

        void display(sf::RenderTarget& render) override;
        void event(const sf::Event&, const network::NetEventPack&) override;

        void displayTrantorInfo(const std::shared_ptr<Trantorian>&);
        void displayTileInfo(void);

    private:

};

} // namespace visual
} // namespace gui


#endif
