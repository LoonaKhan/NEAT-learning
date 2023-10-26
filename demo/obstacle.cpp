//
// Created by loona on 24/10/23.
//

#include "obstacle.h"


Obstacle::Obstacle() {
    this->setFillColor(sf::Color::Blue);
    this->setSize(sf::Vector2f(15, 35));
    this->setOrigin(15, 0);
    this->setPosition(800, 545);

    this->vx = -2;
}

void Obstacle::simulate() {
    this->move(this->vx, 0);

    //if (this->getPosition().x < 50) // delete once it goes offscreen
        //delete this;

}