//
// Created by loona on 24/10/23.
//

#pragma once
#include "SFML/Graphics.hpp"
#include "vector"
#include "obstacle.h"
#include "../textures/textures.h"
#include "../config/config.h"
#include "../nn_models/network.h"


class Player : public sf::RectangleShape {

private: // members
    sf::Vector2f size = {20,30};
    sf::Vector2f sprite_scale = {1.25, 1.25};
    int duck_originy = 30; // we move the origin of the sprite here when ducking
    int jump_speed = 6;// todo: increase this? redo calculations though
    double g = 0.2;
    double terminal_v = 5.0;

public: // members
    double vx,vy;
    bool isDucking;
    sf::RectangleShape &floor;
    nn::Network network;
    int time_lasted; // fitness score
    // senses. nearest obs x and y? todo: did we have notes on this?
    // 3 actions. jump, duck or nothing

public: // methods

    Player(sf::RectangleShape &floor);

    bool simulate(std::vector<Obstacle> &obstacles); // rename to isAlive?

    // Player controls
    void jump(); // sets the velocity. can only jump if colliding with floor

    void duck();

    // senses
    std::vector<float> nearestObstacle(); // detects the x and y position of the nearest obstacle. todo: find the nearest 2?

    // deconstructor too

private: // methods

};
