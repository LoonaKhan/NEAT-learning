//
// Created by loona on 16/10/23.
//

#ifndef DEMO_NETWORK_H
#define DEMO_NETWORK_H

#include <vector>
#include "node.h"
#include <algorithm>


namespace nn {
    struct Network {

        std::vector<std::vector<nn::Node>> nodes;


        Network(int inputs, int layers);

        std::vector<Node> process(std::vector<float> inputs);

    };

}


#endif //DEMO_NETWORK_H
