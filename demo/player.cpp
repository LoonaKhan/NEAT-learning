//
// Created by loona on 24/10/23.
//

#include "player.h"


Player::Player(sf::RectangleShape &floor)
: floor(floor){
    this->setFillColor(sf::Color(255,0,0));
    //this->setScale(5,5);
    this->setSize(sf::Vector2f(20,20));
    this->setOrigin(0,20);
    this->setPosition(10,580);


    this->vy=0, this->vx=0;
    this->isDucking = false;
}

bool Player::simulate(std::vector<Obstacle> &obstacles) {
    this->move(this->vx, this->vy); // move
    if (!this->getGlobalBounds().intersects(this->floor.getGlobalBounds())){ // if not colliding with floor
        this->vy = std::min(5.0, this->vy+0.2); //gravity
    }
    else{
        this->vy=0;
    }
    // check if ducking, if ducking, stop ducking and fix hitbox and sprite
    if (this->isDucking){
        this->isDucking = false;
        this->setSize(sf::Vector2f(20,20));
    }

    // check if colliding with an obstacle, if so, delete
    for (auto& obs : obstacles){
        if (this->getGlobalBounds().intersects(obs.getGlobalBounds())){
            return false; // died
        }
    }
    return true; // alive
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