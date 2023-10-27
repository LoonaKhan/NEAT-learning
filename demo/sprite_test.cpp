//
// Created by loona on 24/10/23.
//
#include "SFML/Graphics.hpp"
#include "player.h"
#include "obstacle.h"
#include "random.hpp"
#include "textures.h"

using Random = effolkronium::random_static;

int main(){
    loadTextures();
    sf::RectangleShape bg(sf::Vector2f(512, 432));
    sf::Texture bgt;
    if (!bgt.loadFromFile("../assets/bg_edited2.png")){
        return -1;
    }
    bg.setTexture(&bgt);
    bg.setScale(1.5625, 1.8519);
    bg.setPosition(0,-120);


    sf::RenderWindow window(sf::VideoMode(800,600), "sprite_test");

    auto floor = sf::RectangleShape(sf::Vector2f(800, 20));
    floor.setPosition(0, 580);
    floor.setTexture(&floor_texture);
    auto plr = Player(floor);
    std::vector<Obstacle> obstacles = {Obstacle()};
    int max_obstacles = 1; // can be dynamic
    int max_distance = 55; // max distance in pixels between each obstacle

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // randomly spawn obstacles
        if (obstacles.size() < max_obstacles and (800 - obstacles[obstacles.size()-1].getPosition().x-15 > max_distance)){ //todo: based on score?. maximum num of obstacles
            obstacles.push_back(Obstacle());
        }
        printf("num obstacles %d\n", obstacles.size());
        for (int i=0; i<obstacles.size(); i++) // remove excess obstacles
            if (obstacles[i].getPosition().x<0)
                obstacles.erase(obstacles.begin()+i);

        // simulate
        bool plrIsAlive = plr.simulate(obstacles);
        for (auto& obs : obstacles) {
            obs.simulate();
        }
        // animation functions

        // controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            plr.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            plr.duck();
        }


        // drawing
        window.draw(bg);
        window.draw(plr);
        for (auto& obs : obstacles){
            window.draw(obs);
        }
        window.draw(floor);



        window.setFramerateLimit(60);
        window.display();
        window.clear();


        if (!plrIsAlive)
            window.close(); // todo: make this just kill the player instead. player array or somn

    }
}