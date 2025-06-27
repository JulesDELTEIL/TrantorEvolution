/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** SoundManage
*/

#ifndef SOUNDMANAGER
    #define SOUNDMANAGER

#include <iostream>
#include <map>
#include <SFML/Audio.hpp>

#include "map_tools.h"

namespace gui {
    const std::map<biome_e, std::string> biome_map =
    {
        {SEA, "../../assets/Trantor.mp3"},
        {FOREST, "../../assets/Trantor.mp3"},
        {MOUNTAINS, "../../assets/Trantor.mp3"},
        {PLAINS, "../../assets/Trantor.mp3"},
        {BEACH, "../../assets/Trantor.mp3"},
        {EMPTY, "../../assets/Trantor.mp3"}
    };
    class SoundManage {
    public:
        SoundManage();
    
    private:
        sf::SoundBuffer sb_song;
        sf::Sound s_song;
    };
}

#endif /* !SOUNDMANAGE_HPP_ */
