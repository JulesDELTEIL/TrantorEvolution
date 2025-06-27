/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** SoundManage
*/

#include "audio/SoundManage.hpp"


void gui::SoundManage::playSong(std::string song)
{
    // "assets/Trantor.mp3"
    if (s_song.getStatus() == sf::SoundSource::Playing) {
        s_song.stop();
    }
    if (!s_song.openFromFile(song)) {
        std::cout << "[ERROR] Trantor.mp3 didn't load" << std::endl;
    }
    s_song.setLoop(true);
    s_song.play();
}
