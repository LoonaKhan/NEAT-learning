//
// Created by loona on 16/10/23.
//

#include "network.h"


nn::Network::Network(int inputs, int layers) {
    // creates a neural network
    for (int i=0; i<layers; i++){
        std::vector<Node> layer;
        for (int j=0; j<inputs; j++){
            Node n;
            if (i == 0){ // creates nodes with no inputs, this is the input layer
                n = Node();
                layer.push_back(n);
            } else {
                n = Node(nodes[i-1]);
                layer.push_back(n);
            }
            //printf("%f\n", n.output);
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

            printf("[%d, %d]: %f\n",i,j, nodes[i][j].output);

        }
    }

    // return the highest of the last layer of nodes
    return nodes[i];
}

void nn::Network::debug() {
    // prints debug info
    // arrangement of nodes as coordinates and their weights
     for (int layer = 0; layer< nodes.size(); layer++) {
         printf("Layer %d: ", layer);
         for (int node=0; node < nodes[layer].size(); node++) {
            printf("{[%d,%d] ", layer, node);
            for (auto & input : nodes[layer][node].inputs){
                //printf("(%f,%f)", input.first->output, input.second);
            }
             printf("}");
         }
         printf("\n");
     }
}