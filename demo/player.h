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

public: // methods

    Player();

    void simulate();

    // Player controls
    void jump(); // sets the velocity. can only jump if colliding with floor

    void duck();

    // deconstructor too

private: // methods

};
