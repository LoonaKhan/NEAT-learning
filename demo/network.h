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


        Network(int inputs, int layers);

        std::vector<Node> process(std::vector<float> inputs);

        void debug();

    };

}


#endif //DEMO_NETWORK_H
