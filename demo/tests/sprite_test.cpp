//
// Created by loona on 24/10/23.
//
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../models/player.h"
#include "../models/obstacle.h"
#include "../random.hpp"
#include "../textures/textures.h"
#include "../music/music.h"
#include "nlohmann/json.hpp"
#include "../config/config.h"

using Random = effolkronium::random_static;
using json = nlohmann::json;


sf::Sound music;
int max_obstacles = 2; // can gradually increase
int max_distance = 250; // max distance in pixels between each obstacle

int main(){
    // load textures, config and audio files
    loadTextures();
    loadSoundBuffers();
    loadConfig();

    // play music
    music.setBuffer(overworld);
    music.play();
    music.setLoop(true);

    sf::Vector2f wsize = {(float)config["wsize"][0], (float)config["wsize"][1]};
    sf::RenderWindow window(sf::VideoMode(wsize.x, wsize.y), "sprite_test"); // draw window

    // sprites
    sf::RectangleShape bg(sf::Vector2f(512, 432));
    bg.setTexture(&bg_texture);
    bg.setScale(1.5625, 1.8519);
    bg.setPosition(0,-120);

    auto floor = sf::RectangleShape(sf::Vector2f(wsize.x, 20));
    floor.setPosition(0, wsize.y-20);
    floor.setTexture(&floor_texture);

    auto plr = Player(floor);

    obstacles = {Obstacle()};

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // randomly spawn obstacles
        if (obstacles.size() < max_obstacles and (wsize.x - obstacles[obstacles.size()-1].getPosition().x-15 > max_distance)){ //todo: based on score?. maximum num of obstacles
            obstacles.push_back(Obstacle());
        }
        //printf("num obstacles %d\n", obstacles.size());
        for (int i=0; i<obstacles.size(); i++) // remove excess obstacles
            if (obstacles[i].getPosition().x<0)
                obstacles.erase(obstacles.begin()+i);

        // simulate
        bool plrIsAlive = plr.simulate(obstacles);
        for (auto& obs : obstacles) {
            obs.simulate();
        }
        auto closest = plr.nearestObstacle(); // senses
        sf::RectangleShape line(sf::Vector2f(closest[0]-plr.getPosition().x, 5));
        line.setPosition(plr.getPosition());
        line.setFillColor(sf::Color::Red);

        // controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            plr.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            plr.duck();
        }
        printf("inputs: [%f, %f]\n", static_cast<float>(1/(1+exp(closest[0] - plr.getPosition().x))), static_cast<float>(1/(1+exp(closest[1] - plr.getPosition().y))));
        std::vector<nn::Node> output = plr.network.process({
                                                                   static_cast<float>(1/(1+exp(closest[0] - plr.getPosition().x))),
                                                                   static_cast<float>(1/(1+exp(closest[1] - plr.getPosition().y)))
        }); // todo: adjust NN to handle larger input numbers better
        if (output[0].output > output[1].output){ // 1st node is greater
            plr.jump();
        } else {
            plr.duck();
        }


        // drawing
        window.draw(bg);
        window.draw(plr);
        for (auto& obs : obstacles){
            window.draw(obs);
        }
        window.draw(floor);
        window.draw(line);



        window.setFramerateLimit(60);
        window.display();
        window.clear();


        if (!plrIsAlive)
            window.close(); // todo: make this just kill the player instead. player array or somn

    }
}