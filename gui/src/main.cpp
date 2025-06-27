/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** main.cpp
*/

#include "project_tools.h"
#include "core/Core.hpp"

int main(int argc, const char *argv[])
{
    gui::core::Core core(argc, argv);

    core.run();
    return PROJECT_SUCCESS;
}
