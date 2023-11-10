//
// Created by loona on 24/10/23.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "../textures/textures.h"
#include "../config/config.h"
#include "../floor/floor.h"
#include "../random.hpp"
#include "vector"

class Obstacle : public sf::RectangleShape {

private:
    sf::Vector2f size = {15, 35};
    sf::Vector2f bullet_size = {32,32};

public:
    double vx=-2;
    std::vector<double> bullet_height = {
            90,// have to be ducked. 90 - 16
            35 + bullet_size.y, // can be ducked or jumped over. 20(part of plr height) + 32 = 52
    };
    Obstacle();

    void simulate();

    bool operator==(const Obstacle& other) const {
        return (this->getPosition() == other.getPosition());
    }

};

extern std::vector<Obstacle> obstacles;

 //DEMO_OBSTACLE_H
