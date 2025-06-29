/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Text.cpp
*/

#include "visual/Text.hpp"

namespace gui {
namespace visual {

Font::Font(const std::string& path)
{
    this->loadFromFile(path);
}

Text::Text(const sf::Font& font, const sf::Color& color, int scale, const std::string& string)
{
    this->setFont(font);
    this->setString(string);
    this->setCharacterSize(scale);
    this->setFillColor(color);
}

}
}