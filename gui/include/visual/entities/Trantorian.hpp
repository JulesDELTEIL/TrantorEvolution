/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.hpp
*/

#ifndef TRANTORIAN_HPP_
    #define TRANTORIAN_HPP_

    #include <memory>
    #include <SFML/Graphics/RenderTarget.hpp>

    #include "visual/entities/ResourceNode.hpp"

    #include "map_tools.h"
    #include "visual/Drawable.hpp"
    #include "visual/Animation.hpp"
    #include "visual/Movement.hpp"

namespace gui {
namespace visual {

    #define NB_TRANTORS 6
    #define TRANTOR_SCALE 0.5f

enum BodyAnimIndex {
    IDLE = 0,
    WALK,
    COLLECT,
    PICKAXE,
    AXE,
};

    #define NB_BODY_ANIM 5

static const std::vector<AnimationInfos> BODY_ANIM_INFOS = {
    {"assets/trantorians/body/Idle_Side-Sheet.png", {64, 64}, {4, 1}, {0, 0}, 0.3, sf::Clock()},
    {"assets/trantorians/body/Walk_Side-Sheet.png", {64, 64}, {6, 1}, {0, 0}, 0.1, sf::Clock()},
    {"assets/trantorians/body/Collect_Side-Sheet.png", {64, 64}, {8, 1}, {0, 0}, 0.2, sf::Clock()},
    {"assets/trantorians/body/Crush_Side-Sheet.png", {64, 64}, {8, 1}, {0, 0}, 0.2, sf::Clock()},
    {"assets/trantorians/body/Slice_Side-Sheet.png", {64, 64}, {8, 1}, {0, 0}, 0.2, sf::Clock()},
    {"assets/trantorians/body/Death_Side-Sheet.png", {64, 64}, {8, 1}, {0, 0}, 0.2, sf::Clock()},
};

class Trantorian {
    public:
        Trantorian(const sf::Vector2f& pos, const sf::Vector2i& pos_in_map,
            size_t level, const std::string& team_name);
        ~Trantorian() = default;

        void draw(sf::RenderTarget&, const sf::Clock&);
        void move(int index, const sf::Vector2f&, float, const sf::Clock&);

        void changeTile(const sf::Vector2f&, float, const sf::Clock&);
        void collect(const std::vector<std::shared_ptr<ResourceNode>>&, float, const sf::Clock&);

        sf::Vector2i map_pos;
        size_t lvl;
        std::string team;
    private:
        sf::Color generateTeamColor(const std::string&);
        std::vector<Drawable> _body;
        std::vector<BodyAnimIndex> _type;
        std::vector<Direction> _body_direction;
        std::vector<Animation> _body_animation;
        std::vector<Movement> _body_movement;
};

} // visual
} // gui

#endif
