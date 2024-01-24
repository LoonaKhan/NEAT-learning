//
// Created by loona on 16/10/23.
//

#ifndef DEMO_NETWORK_H
#define DEMO_NETWORK_H

#include <vector>
#include "node.h"
#include "../ga_models/genome.h"
#include <algorithm>
#include <stdio.h>


namespace nn {
    struct Network {

        std::vector<std::vector<nn::Node>> nodes;

        // topology of the network
        int inputs, outputs, layer_size, hidden_layers;


        Network(int inputs, int outputs, int layer_size, int hidden_layers); // todo: allow parameters for size of input hidden_layers and size of output hidden_layers seperately

        Network(Genome g); // creates a NN from a Genome

        Network();

        std::vector<Node> process(std::vector<float> inputs);

        void debug(bool weights_only=false);

    };

}


#endif //DEMO_NETWORK_H
