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
    const std::map<biome_e, std::string> song_map =
    {
        {SEA, "assets/audio/wave.mp3"},
        {FOREST, "assets/audio/leaf_wind.mp3"},
        {MOUNTAINS, "assets/audio/wind.mp3"},
        {PLAINS, "assets/audio/gazoulli.mp3"},
        {BEACH, "assets/audio/beach.mp3"},
        {EMPTY, ""}
    };
    class SoundManage {
    public:
        SoundManage() = default;
        void playSong(std::string song);
    private:
        sf::SoundBuffer sb_song;
        sf::Music s_song;
    };
}

#endif /* !SOUNDMANAGE_HPP_ */
