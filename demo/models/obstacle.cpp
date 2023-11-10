//
// Created by loona on 24/10/23.
//

#include "obstacle.h"




Obstacle::Obstacle() {
    /*
     * spawns obstacles
     *
     * obstacles can be pipes that are on the ground, or bullet bills that must be ducked under.
     * based on chance
     */

    if (Seeded::get(1,2)== 2){ // pipe
        // add another pipe that is wider. calc how wide it can be at max
        this->setTexture(&obs_textures[0]);
        this->setScale(2.133, 1.83); // todo: add bullet bill and revisit scale
        this->setSize(this->size);
        this->setOrigin(this->size.x, 0);
        this->setPosition((float)config["w_size"][0], (float)config["w_size"][1]-gameFloor.getSize().y-this->size.y);
    } else {
        // bullet bill
        auto height = this->bullet_height[0];

        this->setTexture(&obs_textures[1]);
        this->setSize(this->bullet_size);
        this->setPosition((float)config["w_size"][0], (float)config["w_size"][1] - gameFloor.getSize().y - height);
    }


}

void Obstacle::simulate() {
    this->move(this->vx, 0);

    //if (this->getPosition().x < 50) // delete once it goes offscreen
        //delete this;

}

std::vector<Obstacle> obstacles;