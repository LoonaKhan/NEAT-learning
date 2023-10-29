//
// Created by loona on 16/10/23.
//

#include "network.h"


nn::Network::Network(int inputs, int outputs, int layer_size, int layers) {
    // creates a neural network
    for (int i=0; i<layers; i++){
        std::vector<Node> layer;

        if (i==0){ // input layer
            for (int j=0; j<inputs; j++){
                Node n = Node();
                layer.push_back(n);
            }
        } else if (i== layers-1){
            for (int j=0; j<outputs; j++){
                Node n = Node(nodes[i-1]);
                layer.push_back(n);
            }
        } else {
            for (int j=0; j<layer_size; j++){
                Node n = Node(nodes[i-1]);
                layer.push_back(n);
            }
        }

        nodes.push_back(layer);
    }
}

std::vector<nn::Node> nn::Network::process(std::vector<float> inputs) {
    int i =0;
    for (; i < nodes.size(); i++){

        for (int j=0; j< nodes[i].size(); j++){

            if (i == 0) { // if its in the first layer, pass in the inputs
                nodes[i][j].process(inputs[j]);
            } else {
                nodes[i][j].process();
            }

            //printf("[%d, %d]: %f\n",i,j, nodes[i][j].output);

        }
    }

    //todo: cant access the layer from outside the loop for some reason


    /*for (auto node : nodes[i])
        printf("%f\n", node.output);*/
    return nodes[i-1];
}

void nn::Network::debug() {
    // prints debug info
    // arrangement of nodes as coordinates and their weights
     for (int layer = 0; layer< nodes.size(); layer++) {
         printf("Layer %d: ", layer);
         for (int node=0; node < nodes[layer].size(); node++) {
            printf("{[%d,%d] ", layer, node);
            for (auto & input : nodes[layer][node].inputs){
                printf("(%f,%f)", input.first->output, input.second);
            }
             printf("}");
         }
         printf("\n");
     }
}

void nn::Network::mutate() {
    // iterate through all nodes
    // random chance of modifying weights. how likely?
    // how much do we change the weights. should be adjusted, not reset
    for (auto& layer : nodes) {
        for (auto& node : layer) {
            for (auto& [_, weight] : node.inputs){
                if (Random::get(1,10) == 10){ // chance of adjusting weights
                    weight += Random::get(-0.5, 0.5);
                    weight = std::max(std::min(weight, 1.0f), -1.0f);
                }
            }
        }
    }
}