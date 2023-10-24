//
// Created by loona on 24/10/23.
//

#include "player.h"


Player::Player() {
    this->setFillColor(sf::Color(255,0,0));
    //this->setScale(5,5);
    this->setSize(sf::Vector2f(20,20));
    this->setPosition(500,500);

    this->vy=0, this->vx=0;
    this->isDucking = false;
}

void Player::simulate() {
    this->move(this->vx, this->vy); // move
    this->vy+=0.2;//gravity
    // check if ducking, if ducking, stop ducking and fix hitbox and sprite
}

void Player::jump() {
    this->vy -=1;
}

void Player::duck() {
    this->setSize(sf::Vector2f(10,20));
    this->isDucking = true;
    // change sprite
}