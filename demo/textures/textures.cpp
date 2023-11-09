//
// Created by loona on 26/10/23.
//

#include "textures.h"
#include "stdio.h"

// set these texture vectors to unordered maps?
std::vector<sf::Texture> plr_textures;
std::vector<sf::Texture> obs_textures;
sf::Texture floor_texture;

sf::Texture bg_texture;

void loadTextures(){
    loadPlrTextures();
    loadObsTextures();
    loadFloor();
    loadBg();

}

void loadPlrTextures() {
    sf::Texture idle, lookup, duck, walk0, walk1, walk2, jump, fall;

    if (!idle.loadFromFile("../assets/mario-sheet.png", sf::IntRect(24, 40, 16, 24))){
        printf("could not load texture: idle\n");
        exit(1);
    }
    plr_textures.push_back(idle);

    if (!lookup.loadFromFile("../assets/mario-sheet.png", sf::IntRect(76, 40, 16, 24))){
        printf("could not load texture: lookup\n");
        exit(1);
    }
    plr_textures.push_back(lookup);

    if (!duck.loadFromFile("../assets/mario-sheet.png", sf::IntRect(128, 40, 16, 24))){
        printf("could not load texture: duck\n");
        exit(1);
    }
    plr_textures.push_back(duck);

    if (!walk0.loadFromFile("../assets/mario-sheet.png", sf::IntRect(180, 40, 16, 24))){
        printf("could not load texture: walk0\n");
        exit(1);
    }
    plr_textures.push_back(walk0);

    if (!walk1.loadFromFile("../assets/mario-sheet.png", sf::IntRect(232, 40, 16, 24))){
        printf("could not load texture: walk1\n");
        exit(1);
    }
    plr_textures.push_back(walk1);

    if (!walk2.loadFromFile("../assets/mario-sheet.png", sf::IntRect(284, 40, 16, 24))){
        printf("could not load texture: walk2\n");
        exit(1);
    }
    plr_textures.push_back(walk2);

    if (!jump.loadFromFile("../assets/mario-sheet.png", sf::IntRect(336, 40, 16, 24))){
        printf("could not load texture: jump\n");
        exit(1);
    }
    plr_textures.push_back(jump);

    if (!fall.loadFromFile("../assets/mario-sheet.png", sf::IntRect(388, 40, 16, 24))){
        printf("could not load texture: fall\n");
        exit(1);
    }
    plr_textures.push_back(fall);
}

void loadObsTextures(){
    sf::Texture pipe, bullet_bill;

    if (!pipe.loadFromFile("../assets/pipe.png")){
        printf("could not load texture: pipe\n");
        exit(1);
    }
    obs_textures.push_back(pipe);

    if (!bullet_bill.loadFromFile("../assets/bullet-bill.png")){
        printf("could not load texture: bullet bill\n");
        exit(1);
    }
    obs_textures.push_back(bullet_bill);
}

void loadFloor() {
    if (!floor_texture.loadFromFile("../assets/floor.png")){
        printf("could not load texture: floor\n");
        exit(1);
    }
}

void loadBg(){
    if (!bg_texture.loadFromFile("../assets/bg_edited.png")){
        printf("could not load texture: bg\n");
        exit(1);
    }
}