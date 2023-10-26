//
// Created by loona on 24/10/23.
//
#include "SFML/Graphics.hpp"
#include "player.h"
#include "obstacle.h"
#include "random.hpp"

using Random = effolkronium::random_static;

std::vector<Obstacle> obstacles;

int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "sprite_test");

    auto floor = sf::RectangleShape(sf::Vector2f(800, 20));
    floor.setPosition(0, 580);
    floor.setFillColor(sf::Color::White);
    auto plr = Player(floor);
    //auto obs = Obstacle();

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // randomly spawn obstacles
        if (Random::get(1,200) == 1){ // 200 is frequency. todo: based on score?
            obstacles.push_back(Obstacle());
        }
        printf("num obstacles %d\n", obstacles.size());
        for (int i=0; i<obstacles.size(); i++) // remove excess obstacles
            if (obstacles[i].getPosition().x<0)
                obstacles.erase(obstacles.begin()+i);

        // simulate
        bool plrIsAlive = plr.simulate(obstacles);
        if (!plrIsAlive)
            window.close(); // todo: make this just kill the player instead. player array or somn
        for (auto& obs : obstacles) {
            obs.simulate();
        }

        // controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            plr.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            plr.duck();
        }

        window.draw(floor);
        window.draw(plr);
        for (auto& obs : obstacles){
            window.draw(obs);
        }



        window.setFramerateLimit(60);
        window.display();
        window.clear();

    }
}