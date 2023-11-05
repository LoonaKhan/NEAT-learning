//
// Created by loona on 24/10/23.
//

#include "player.h"

#include <utility>


std::vector<Player> players;
std::vector<Player> deadPlayers;
int id = 0;

Player::Player(sf::RectangleShape *floor)
: floor(floor), network(nn::Network(4,2,3,5)){
    this->setTexture(&plr_textures[0]);

    this->setScale(this->sprite_scale);
    this->setSize(this->size);
    this->setOrigin(0,this->size.y);
    this->setPosition(100,(float)config["w_size"][1]-20);
    //this->ID = id++;


    this->vy=0, this->vx=0;
    this->isDucking = false;
}

Player::Player(){}

bool Player::simulate(std::vector<Obstacle> &obstacles) {

    // increase the frame counter
    this->framecounter++;

    // check if ducking, if ducking, stop ducking and fix hitbox and sprite
    if (this->isDucking){// check if key being pressed?
        this->isDucking = false;
        this->setSize(this->size);
        this->setOrigin(0,this->size.y);
        this->setTexture(&plr_textures[0]);
    }

    this->move(this->vx, this->vy); // move
    if (this->framecounter % 5 ==0) {
        this->animate();
    }

    if (!this->getGlobalBounds().intersects(this->floor->getGlobalBounds())){ // if not colliding with gameFloor
        this->vy = std::min(terminal_v, this->vy+g); //gravity
        if (this->vy >0)
            this->setTexture(&plr_textures[7]);
    }
    else{
        if (this->vy !=0) // when the player lands, reset the animation frame to idle
            this->setTexture(&plr_textures[0]);
        this->vy=0;
    }

    // check if colliding with an obstacle, if so, delete
    for (auto& obs : obstacles){
        if (this->getGlobalBounds().intersects(obs.getGlobalBounds())){
            return false; // died
        }
    }
    return true; // alive
}

void Player::jump() {
    if (this->getGlobalBounds().intersects(this->floor->getGlobalBounds())) {
        this->vy -= jump_speed;
        this->setTexture(&plr_textures[6]);
    }
}

void Player::duck() { // check if the hitbox is set properly
    this->setSize(this->size);
    this->isDucking = true;
    this->setOrigin(0,this->duck_originy);
    // change sprite
    this->setTexture(&plr_textures[2]);
}

Obstacle Player::nearestObstacle(std::vector<Obstacle> &obstacles_list) {
    //std::vector<float> ret = {0,0};
    auto nearest_obs = obstacles_list[0];
    for (const auto& obs : obstacles_list) {
        float curr_dist = (this->getPosition().x - obs.getPosition().x); // magnitude of dist from
        if (curr_dist < 0 and ((this->getPosition().x - nearest_obs.getPosition().x) > 0)){
            nearest_obs = obs;
        }
    }
    return nearest_obs;
}

void Player::animate() {
    // if texture is idle or walk2, set to walk0
    if (this->getTexture() == &plr_textures[0] or this->getTexture() == &plr_textures[5]){
        this->setTexture(&plr_textures[3]);
    } else if (this->getTexture() == &plr_textures[3]){ // if walk0, set to walk1
        this->setTexture(&plr_textures[4]);
    } else if (this->getTexture() == &plr_textures[4]) { // if walk1, set to walk2
        this->setTexture(&plr_textures[5]);
    }
}


std::pair<nn::Network, nn::Network> selectParents(std::vector<Player> deadPlayers) {
    // Selects the parents for the next generation
    // Players with higher fitness scores are more likely to get chosen
    // we organize all players in a list and find the sum of their fitness scores
    // we generate random numbers and iterate through the list and subtract fitness until we are below 0
    // we then select that player as a parent and repeat for the 2nd parent
    // todo: look into better algorithms for this


    // get the sum of the fitness scores
    int sum=0;
    float avg;
    for (auto& plr : deadPlayers){
        sum += plr.framecounter;
        printf("fitness score: %d\n",plr.framecounter);
    }
    avg = sum / deadPlayers.size();
    printf("average fitness score of population: %f\n", avg);

    auto first_parent_chance = Random::get(0, sum),
    second_parent_chance = Random::get(0, sum);
    nn::Network first_parent, second_parent;

    // choose the NN for the first parent
    Player chosenPlayer;
    for (auto& plr : deadPlayers){
        if (first_parent_chance < plr.framecounter) { // todo: always subtract and check if <0
            first_parent =plr.network;
            chosenPlayer = plr;
            printf("first parent fitness score: %d\n", plr.framecounter);
            break;
        } else {
            first_parent_chance -= plr.framecounter;
        }
    }

    // remove the chosen player so we dont choose it again
    auto it = std::find(deadPlayers.begin(), deadPlayers.end(), chosenPlayer);
    deadPlayers.erase(it);

    // choose the NN for the 2nd parent
    for (auto& plr : deadPlayers){
        if (second_parent_chance < plr.framecounter) {
            second_parent =plr.network;
            printf("second parent fitness score: %d\n", plr.framecounter);
            break;
        } else {
            second_parent_chance -= plr.framecounter;
        }
    }

    first_parent.debug(true);
    printf("\n");
    second_parent.debug(true);
    printf("\n");

    return {first_parent, second_parent};

}

nn::Network createOffspring(std::pair<nn::Network, nn::Network> parents){
    /*
     * Here we create the offspring from the parents to serve as the base of the next generation
     *
     * We iterate through each node's weights in each layer of each network and determine if we should recombine.
     * If so, we swap nodes from that node to the rest of the layer.
     * This involves swapping those weight values.
     */

    auto p1 = parents.first.nodes,
         p2 = parents.second.nodes;
    auto offspring = parents.first;

    for (int l = 0; l < p2.size(); l++) {
        for (int n=0; n < p2[l].size(); n++) {
            bool recombine = false;
            for (int i = 0; i < p2[l][n].inputs.size(); i++){
                if (!recombine and Random::get(1,5) == 1) // todo: dont make this a magic number
                    recombine = true;
                if (recombine) { // swap
                    offspring.nodes[l][n].inputs[i].second = p2[l][n].inputs[i].second;
                    // todo: maybe change threshold too?
                }
            }
        }
    }

    return offspring;
}

void createPopulation(nn::Network offspring) {
    Player og = Player(&gameFloor); // todo: move gameFloor to a global variable or somn
    og.network = std::move(offspring);
    players.assign(config["pop_size"], og); // offspring gets to participate with the new population

    for (auto& plr : players) {
        plr.network.mutate();
    }
}