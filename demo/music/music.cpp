//
// Created by loona on 27/10/23.
//

#include "music.h"

sf::SoundBuffer overworld;
sf::SoundBuffer athletic;

void loadSoundBuffers(){
    if (!overworld.loadFromFile("../assets/overworld.wav")){
        printf("failed to load song: overworld\n");
        exit(1);
    }
    if (!athletic.loadFromFile("../assets/athletic.wav")){
        printf("failed to load song: athletic\n");
        exit(1);
    }
}