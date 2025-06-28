/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Teams.hpp
*/

#ifndef TEAMS_HPP_
    #define TEAMS_HPP_

    #include <vector>

    #include "visual/entities/Trantorian.hpp"

namespace gui {
namespace visual {

    #define RANDOM_COLOR sf::Color(std::rand() + 255, std::rand() + 255, std::rand() + 255)

struct TeamInfo {
    std::string name;
    sf::Color color;
    std::vector<std::shared_ptr<Trantorian>> trantorians;
};

typedef std::vector<TeamInfo> Teams;

} // visual
} // gui

#endif
