//
// Created by loona on 05/11/23.
//

#include "objects.h"


sf::RectangleShape gameFloor;

void loadGameFloor(){
    gameFloor = sf::RectangleShape(sf::Vector2f(config["w_size"][0], 20));
    gameFloor.setPosition(0, (int)config["w_size"][1]-20);
    gameFloor.setTexture(&floor_texture);
}