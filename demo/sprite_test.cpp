//
// Created by loona on 24/10/23.
//
#include "SFML/Graphics.hpp"
#include "player.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "sprite_test");

    auto floor = sf::RectangleShape(sf::Vector2f(800, 20));
    floor.setPosition(0, 580);
    floor.setFillColor(sf::Color::White);
    auto plr = Player(floor);

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // simulate
        plr.simulate();

        // controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            plr.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            plr.duck();
        }

        window.draw(plr);
        window.draw(floor);


        window.setFramerateLimit(60);
        window.display();
        window.clear();

    }
}