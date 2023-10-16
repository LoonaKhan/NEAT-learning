//
// Created by loona on 16/10/23.
//

#include "network.h"


nn::Network::Network(int inputs, int layers) {
    // creates a neural network
    for (int i=0; i<layers; i++){
        std::vector<Node> layer;
        for (int j=0; j<inputs; j++){
            if (i == 0){ // creates nodes with no inputs, this is the input layer
                layer.push_back(Node());
            } else {
                layer.push_back(Node(nodes[i-1]));
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

        }
    }

    // return the highest of the last layer of nodes
    return nodes[i];
}