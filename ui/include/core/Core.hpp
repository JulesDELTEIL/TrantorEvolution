/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Core.hpp
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <map>

    #include "core/Window.hpp"

namespace gui {
namespace core {

class Core {
    public:
        Core();
        ~Core() = default;

    private:
        Window _window;

};

} // core
} // core

#endif
