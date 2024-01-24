#pragma once

#include <vector>
#include "../random.hpp"

using Random = effolkronium::random_static;

// organize this, possibly a inputNode subclass

namespace nn {
struct Node {
    // inputs, activate, output
    std::vector<const Node*> inputs; // output of the node and its weight
    //int num_inputs;
    std::vector<float> weights; // contains weights. threshold included so we can easily modify it
    float output;

    Node(); // for input nodes
    Node(std::vector<Node> &last_layer);

    void activate(float input);// for the first layer

    void activate(); // all other layers

};


}