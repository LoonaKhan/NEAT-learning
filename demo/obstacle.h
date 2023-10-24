//
// Created by loona on 24/10/23.
//

#pragma once

#include "SFML/Graphics.hpp"

class Obstacle : public sf::RectangleShape {
public:
    double vx;

    Obstacle();

    void simulate();

};

 //DEMO_OBSTACLE_H
