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
#include "floor/floor.h"
#include "text/text.h"
#include "rand/rand.h"
#include <string>

using Random = effolkronium::random_static;
using json = nlohmann::json;


sf::Sound music;
int max_obstacles = 2; // can gradually increase
int max_distance = 200; // max distance in pixels between each obstacle




int main(){
    // set seed
    //Seeded::seed(1);
    setSeed();

    // load textures, config and audio files
    loadFonts();
    loadText();
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
        if (obstacles.size() < max_obstacles and (obstacles.size()==0 or (wsize.x - obstacles[obstacles.size()-1].getPosition().x-15 > max_distance))){ //todo: based on score?. maximum num of obstacles
            auto c = Seeded::get(1,50);
            if ( c== 1) obstacles.push_back(Obstacle());
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
                continue;
            }

            if (obstacles.size() > 0){ //todo: make the fitness score increment even if there are no obstacles

                // get senses
                auto closestObs = plr.nearestObstacle(obstacles);
                auto editedObstacles = obstacles;
                auto it = std::find(editedObstacles.begin(), editedObstacles.end(), closestObs);
                if (editedObstacles.size() > 0)
                    editedObstacles.erase(it);

                auto nextClosestObs = plr.nearestObstacle(editedObstacles);

                auto output = plr.network.process({
                                                          plr.getPosition().y, // player's y position
                                                          closestObs.getPosition().x - plr.getPosition().x, // nearest obs x
                                                          (float)config["w_size"][1] - closestObs.getPosition().y, // nearest obs height
                                                          closestObs.getGlobalBounds().width, // nearest obs width
                                                          (float)closestObs.vx, // nearest obs speed
                                                          nextClosestObs.getPosition().x - plr.getPosition().x, // 2nd nearest obs x,
                                                          (float)config["w_size"][1] - nextClosestObs.getPosition().y, // 2nd nearest obstacle height
                                                          closestObs.getGlobalBounds().width, // 2nd nearest obstacle width
                                                          nextClosestObs.getPosition().x - closestObs.getPosition().x // distance between obstacles
                                                  });
                //printf("plr hight: %f\n",  - plr.getPosition().y);


                // todo: determine largest element, so we can have 3 inputs?
                int max_element = 0;
                for (int i=0; i < output.size(); i++){
                    if (output[i].output > output[max_element].output)
                        max_element = i;
                }

                if (max_element == 0) {
                    //printf("jumping\n");
                    if (plr.vy ==0){
                        plr.jump();
                    }
                } else if (max_element ==1){
                    plr.duck();
                } else {}
            }
            window.draw(plr);
        }
        // remove old players
        for (auto plr : toRemove) {
            auto it = std::find(players.begin(), players.end(), *plr);
            players.erase(it);
        }

        // once all players are dead, process the population and prepare the next generation
        if (players.empty()) {
            printf("Generation: %d\n", generation);
            players.clear();
            obstacles.clear();

            auto parents = selectParents(deadPlayers);
            auto offspring = createOffspring(parents);

            createPopulation(offspring);
            deadPlayers.clear();
            generation++;

            setSeed();
            obstacles.push_back(Obstacle());
        }

        // draw test info to screen
        generation_text.setString("Generation: " + std::to_string(generation));
        first_parent_text.setString("First parent fitness score: " + std::to_string(first_parent_fitness));
        second_parent_text.setString("Second parent fitness score: "+ std::to_string(second_parent_fitness));
        top_performer_text.setString("Top performer of last gen: " + std::to_string(top_performer));
        top_performer_alltime_text.setString("Top performer of all time: " + std::to_string(top_performer_alltime));
        window.draw(generation_text);
        window.draw(first_parent_text);
        window.draw(second_parent_text);
        window.draw(top_performer_text);
        window.draw(top_performer_alltime_text);

        
        // draw stuff to screen
        window.setFramerateLimit(60*(int)config["sim_speed"]);
        window.display();
        window.clear();

    }
}