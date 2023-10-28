//
// Created by loona on 24/10/23.
//

#include "obstacle.h"


Obstacle::Obstacle() {
    //this->setFillColor(sf::Color::Blue);
    this->setTexture(&obs_textures[0]);
    this->setScale(2.133, 1.83); // todo: add bullet bill and revisit scale
    this->setSize(this->size);
    this->setOrigin(this->size.x, 0);
    this->setPosition((float)config["wsize"][0], (float)config["wsize"][1]-55);
}

void Obstacle::simulate() {
    this->move(this->vx, 0);

    //if (this->getPosition().x < 50) // delete once it goes offscreen
        //delete this;

}