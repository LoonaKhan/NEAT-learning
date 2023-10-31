//
// Created by loona on 24/10/23.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "../textures/textures.h"
#include "../config/config.h"
#include "vector"

class Obstacle : public sf::RectangleShape {

private:
    sf::Vector2f size = {15, 35};

public:
    double vx=-2;

    Obstacle();

    void simulate();

    bool operator==(const Obstacle& other) const {
        return (this->getPosition() == other.getPosition());
    }

};

extern std::vector<Obstacle> obstacles;

 //DEMO_OBSTACLE_H
