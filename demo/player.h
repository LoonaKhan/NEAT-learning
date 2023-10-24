//
// Created by loona on 24/10/23.
//

#pragma once
#include "SFML/Graphics.hpp"


class Player : public sf::RectangleShape {

private: // members

public: // members
    double x,y,vx,vy;
    bool isDucking;
    sf::RectangleShape &floor;

public: // methods

    Player(sf::RectangleShape &floor);

    void simulate();

    // Player controls
    void jump(); // sets the velocity. can only jump if colliding with floor

    void duck();

    // senses

    // deconstructor too

private: // methods

};
