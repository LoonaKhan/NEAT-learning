//
// Created by loona on 16/10/23.
//

#ifndef DEMO_NETWORK_H
#define DEMO_NETWORK_H

#include <vector>
#include "node.h"
#include <algorithm>
#include <stdio.h>


namespace nn {
    struct Network {

        std::vector<std::vector<nn::Node>> nodes;


        Network(int inputs, int outputs, int layer_size, int layers); // todo: allow parameters for size of input layers and size of output layers seperately

        std::vector<Node> process(std::vector<float> inputs);

        void debug();

        void mutate();

    };

}


#endif //DEMO_NETWORK_H
