/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** SoundManage
*/

#ifndef SOUNDMANAGER
    #define SOUNDMANAGER

#include <iostream>
#include <SFML/Audio.hpp>

namespace gui {
    class SoundManage {
    public:
        SoundManage();
    
    private:
        sf::SoundBuffer sb_song;
        sf::Sound s_song;
    };
}

#endif /* !SOUNDMANAGE_HPP_ */
