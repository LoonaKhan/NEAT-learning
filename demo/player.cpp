//
// Created by loona on 24/10/23.
//

#include "player.h"


Player::Player(sf::RectangleShape &floor)
: floor(floor){
    this->setTexture(&plr_textures[0]);

    this->setScale(1.25, 1.25);
    this->setSize(sf::Vector2f(20,30));
    this->setOrigin(0,30);
    this->setPosition(10,580);


    this->vy=0, this->vx=0;
    this->isDucking = false;
}

bool Player::simulate(std::vector<Obstacle> &obstacles) {

    // check if ducking, if ducking, stop ducking and fix hitbox and sprite
    if (this->isDucking){// check if key being pressed?
        this->isDucking = false;
        this->setSize(sf::Vector2f(20,30));
        this->setOrigin(0,30);
        this->setTexture(&plr_textures[0]);
    }

    this->move(this->vx, this->vy); // move
    if (!this->getGlobalBounds().intersects(this->floor.getGlobalBounds())){ // if not colliding with floor
        this->vy = std::min(5.0, this->vy+0.2); //gravity
        if (this->vy >0)
            this->setTexture(&plr_textures[7]);
    }
    else{
        this->vy=0;
        this->setTexture(&plr_textures[0]);
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
        this->setTexture(&plr_textures[6]);
    }
}

void Player::duck() {
    this->setSize(sf::Vector2f(20,20));
    this->isDucking = true;
    this->setOrigin(0,13.5);
    // change sprite
    this->setTexture(&plr_textures[2]);
}