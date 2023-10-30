//
// Created by loona on 24/10/23.
//

#include "player.h"


Player::Player(sf::RectangleShape &floor)
: floor(floor), network(nn::Network(2,2,3,5)){
    this->setTexture(&plr_textures[0]);

    this->setScale(this->sprite_scale);
    this->setSize(this->size);
    this->setOrigin(0,this->size.y);
    this->setPosition(100,(float)config["wsize"][1]-20);


    this->vy=0, this->vx=0;
    this->isDucking = false;
}

bool Player::simulate(std::vector<Obstacle> &obstacles) {

    // check if ducking, if ducking, stop ducking and fix hitbox and sprite
    if (this->isDucking){// check if key being pressed?
        this->isDucking = false;
        this->setSize(this->size);
        this->setOrigin(0,this->size.y);
        this->setTexture(&plr_textures[0]);
    }

    this->move(this->vx, this->vy); // move
    if (!this->getGlobalBounds().intersects(this->floor.getGlobalBounds())){ // if not colliding with floor
        this->vy = std::min(terminal_v, this->vy+g); //gravity
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
        this->vy -= jump_speed;
        this->setTexture(&plr_textures[6]);
    }
}

void Player::duck() { // check if the hitbox is set properly
    this->setSize(this->size);
    this->isDucking = true;
    this->setOrigin(0,this->duck_originy);
    // change sprite
    this->setTexture(&plr_textures[2]);
}

std::vector<float> Player::nearestObstacle() {
    std::vector<float> ret = {0,0};
    auto nearest_obs = obstacles[0];
    for (const auto& obs : obstacles) {
        float curr_dist = (this->getPosition().x - obs.getPosition().x); // magnitude of dist from
        if (curr_dist < 0 and ((this->getPosition().x - nearest_obs.getPosition().x) > 0)){
            nearest_obs = obs;
        }
    }
    return {nearest_obs.getPosition().x,
            nearest_obs.getPosition().y};
}