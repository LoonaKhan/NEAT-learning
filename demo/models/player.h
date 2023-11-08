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
#include "../objects.h"

extern int id; // ID's to differentiate players
class Player : public sf::RectangleShape {

private: // members
    sf::Vector2f size = {20, 30};
    sf::Vector2f sprite_scale = {1.25, 1.25};
    int duck_originy = 30; // we move the origin of the sprite here when ducking
    int jump_speed = 6;// todo: increase this? redo calculations though
    double g = 0.2;
    double terminal_v = 5.0;
    int ID=id++;

public: // members
    double vx,vy;
    bool isDucking;
    sf::RectangleShape *floor;
    nn::Network network;
    int framecounter=0; // frame counter to keep track of animations. use as fitness score?
    // 3 actions. jump, duck or nothing
    int pipes_jumped=0;
    int fitness_score=0;
public: // methods

    Player(sf::RectangleShape *floor); // todo: reform to allow inputting a NN
    Player();

    bool simulate(std::vector<Obstacle> &obstacles); // rename to isAlive?

    // Player controls
    void jump(); // sets the velocity. can only jump if colliding with gameFloor

    void duck();

    // senses
    Obstacle nearestObstacle(std::vector<Obstacle> &obstacles_list); // detects the x and y position of the nearest obstacle. todo: find the nearest 2?

    // deconstructor too

    // operators
    bool operator==(Player other) const {
        return (this->ID == other.ID);
    }

    // animation
    void animate();

    void evalFitness();

private: // methods

};

extern std::vector<Player> players; // vector to hold players
extern std::vector<Player> deadPlayers; // stores dead players

// todo: put these into a seperate file for creating the next generation. breeeding?
std::pair<nn::Network, nn::Network> selectParents(std::vector<Player> deadPlayers);

nn::Network createOffspring(std::pair<nn::Network, nn::Network> parents);

void createPopulation(nn::Network offspring);
