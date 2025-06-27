/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** SoundManage
*/

#include "audio/SoundManage.hpp"

gui::SoundManage::SoundManage()
{
    if (!s_song.openFromFile("assets/Trantor.mp3")) {
        std::cout << "[ERROR] Trantor.mp3 didn't load" << std::endl;
    }
    s_song.setLoop(true);
    s_song.play();
}
