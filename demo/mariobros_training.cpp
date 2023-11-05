//
// Created by loona on 24/10/23.
//
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "models/player.h"
#include "models/obstacle.h"
#include "random.hpp"
#include "textures/textures.h"
#include "music/music.h"
#include "nlohmann/json.hpp"
#include "config/config.h"
#include "objects.h"

using Random = effolkronium::random_static;
using json = nlohmann::json;


sf::Sound music;
int max_obstacles = 2; // can gradually increase
int max_distance = 200; // max distance in pixels between each obstacle

int main(){
    // load textures, config and audio files
    loadTextures();
    loadSoundBuffers();
    loadConfig();
    loadGameFloor();

    // play music
    music.setBuffer(overworld);
    music.play();
    music.setLoop(true);

    // draw window
    sf::Vector2f wsize = {(float)config["w_size"][0], (float)config["w_size"][1]};
    sf::RenderWindow window(sf::VideoMode(wsize.x, wsize.y), "sprite_test");

    // sprites
    sf::RectangleShape bg(sf::Vector2f(512, 432));
    bg.setTexture(&bg_texture);
    bg.setScale(1.5625, 1.8519);
    bg.setPosition(0,-120);

    /*auto floor = sf::RectangleShape(sf::Vector2f(wsize.x, 20));
    floor.setPosition(0, wsize.y-20);
    floor.setTexture(&floor_texture);*/

    // setup players
    for (int i=0; i<config["pop_size"]; i++)
        players.push_back(Player(&gameFloor));

    obstacles.push_back(Obstacle());


    // GAME LOOP
    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // randomly spawn obstacles if we arent at max obstacles and the last obstacle is sufficiently spaced from the 2nd last one
        if (obstacles.size() < max_obstacles and (wsize.x - obstacles[obstacles.size()-1].getPosition().x-15 > max_distance)){ //todo: based on score?. maximum num of obstacles
            if (Random::get(1,100) == 1) obstacles.push_back(Obstacle());
        }

        // remove excess obstacles
        for (int i=0; i<obstacles.size(); i++)
            if (obstacles[i].getPosition().x<0)
                obstacles.erase(obstacles.begin()+i);

        // drawing
        window.draw(bg);
        for (auto& obs : obstacles){
            obs.simulate();
            window.draw(obs);
        }
        window.draw(gameFloor);

        // simulate all players
        std::vector<Player*> toRemove;
        for (auto& plr : players){

            bool alive = plr.simulate(obstacles);
            if (!alive) {
                deadPlayers.push_back(plr);
                // remove from players
                toRemove.push_back(&plr);
            }

            if (obstacles.size() > 0){
                auto closestObs = plr.nearestObstacle(obstacles);

                auto editedObstacles = obstacles;
                auto it = std::find(editedObstacles.begin(), editedObstacles.end(), closestObs);
                if (editedObstacles.size() > 0)
                    editedObstacles.erase(it);
                //printf("size of  obstacles: %d and edited obstacles: %d\n", obstacles.size(), editedObstacles.size());

                auto nextClosestObs = plr.nearestObstacle(editedObstacles);

                auto output = plr.network.process({
                                                          closestObs.getPosition().x - plr.getPosition().x,
                                                          closestObs.getPosition().y - plr.getPosition().y,
                                                          nextClosestObs.getPosition().x - plr.getPosition().x,
                                                          nextClosestObs.getPosition().y - plr.getPosition().y
                                                  });
                /*printf("inputs: [%f, %f, %f, %f]\n\n",
                       closestObs.getPosition().x - plr.getPosition().x,
                       closestObs.getPosition().y - plr.getPosition().y,
                       nextClosestObs.getPosition().x - plr.getPosition().x,
                       nextClosestObs.getPosition().y - plr.getPosition().y
                );*/

                if (output[0].output > output[1].output) {
                    plr.jump();
                } else {
                    plr.duck();
                }
            }
            window.draw(plr);
        }
        // remove old players
        for (auto plr : toRemove) {
            auto it = std::find(players.begin(), players.end(), *plr);
            players.erase(it);
        }

        // once all players are dead, process the population and prepare the next generation
        if (players.empty() ) {
            obstacles.clear();
            obstacles.push_back(Obstacle());
            auto offspring = createOffspring(selectParents(deadPlayers));
            offspring.debug(true);
            createPopulation(offspring);
            //break;
        }
        
        // draw stuff to screen
        window.setFramerateLimit(60);
        window.display();
        window.clear();

    }
}