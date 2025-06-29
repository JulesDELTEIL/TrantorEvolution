/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Text.hpp
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include <SFML/Graphics/Text.hpp>
    #include <string>

namespace gui {
namespace visual {

struct Font : public sf::Font {
    Font(const std::string&);
};

struct Text : public sf::Text {
    Text(const sf::Font&, const sf::Color& = sf::Color::White, int = 32, const std::string& = "");
};

} // visual
} // gui

#endif