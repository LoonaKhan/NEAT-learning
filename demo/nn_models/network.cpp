//
// Created by loona on 16/10/23.
//

#include "network.h"


nn::Network::Network(int inputs, int outputs, int layer_size, int hidden_layers) {
    // creates a neural network

    std::vector<Node> flayer, llayer;
    for (int inp=0; inp < inputs;inp++){
        Node n = Node();
        flayer.push_back(n);
    }
    nodes.push_back(flayer);

    for (int i=0; i < hidden_layers; i++){
        std::vector<Node> layer;
        for (int j=0; j<layer_size; j++){
            Node n = Node(nodes[i]);
            layer.push_back(n);
        }
        nodes.push_back(layer);
    }
    for (int out=0; out<outputs; out++){
        Node n = Node(nodes[nodes.size()-1]);
        llayer.push_back(n);
    }
    nodes.push_back(llayer);
}

nn::Network::Network(){}

std::vector<nn::Node> nn::Network::process(std::vector<float> inputs) {
    int i =0;
    for (; i < nodes.size(); i++){

        for (int j=0; j< nodes[i].size(); j++){

            if (i == 0) { // if its in the first layer, pass in the inputs
                nodes[i][j].activate(inputs[j]);
            } else {
                nodes[i][j].activate();
            }

            //printf("[%d, %d]: %f\n",i,j, nodes[i][j].output);

        }
    }

    return nodes[nodes.end()-nodes.begin()-1];
}

void nn::Network::debug(bool weights_only) {
    // prints debug info
    // arrangement of nodes as coordinates and their weights
     for (int layer = 0; layer< nodes.size(); layer++) {
         printf("Layer %d: ", layer);
         for (int node=0; node < nodes[layer].size(); node++) {
            printf("{[%d,%d] ", layer, node);
            for (auto & input : nodes[layer][node].inputs){
                if (!weights_only)
                    printf("(%f,%f)", input.first->output, input.second);
                else
                    printf("(%f)", input.second);
            }
             printf("}  ");
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
                if (Random::get(1,50) == 10){ // chance of adjusting weights
                    weight += Random::get(-0.5, 0.5);
                    weight = std::max(std::min(weight, 1.0f), -1.0f);
                }
            }
        }
    }
}