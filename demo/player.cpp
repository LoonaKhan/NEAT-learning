//
// Created by loona on 24/10/23.
//

#include "player.h"


Player::Player(sf::RectangleShape &floor)
: floor(floor){
    this->setFillColor(sf::Color(255,0,0));
    //this->setScale(5,5);
    this->setSize(sf::Vector2f(20,20));
    this->setPosition(10,500);

    this->vy=0, this->vx=0;
    this->isDucking = false;
}

void Player::simulate() {
    this->move(this->vx, this->vy); // move
    if (!this->getGlobalBounds().intersects(this->floor.getGlobalBounds())) // if not colliding with floor
        this->vy+=0.2;//gravity
    else
        this->vy=0;
    // check if ducking, if ducking, stop ducking and fix hitbox and sprite
    if (this->isDucking){
        this->isDucking = false;
        this->setSize(sf::Vector2f(20,20));
    }
}

void Player::jump() {
    if (this->getGlobalBounds().intersects(this->floor.getGlobalBounds())) {
        this->vy -= 5;
    }
}

void Player::duck() {
    this->setSize(sf::Vector2f(20,10));
    this->isDucking = true;
    // change sprite
}