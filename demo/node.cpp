#include "node.h"

nn::Node::Node(std::vector<Node> &last_layer) {
    for (auto const& node : last_layer){
        // for each node, assign a weight to it and append to inputs
        std::pair<const Node*, float> p;
        p.first = &node;
        p.second = Random::get(-1.0, 1.0);
        inputs.push_back(p);
        output = 0.0f;
    }
}

nn::Node::Node(){
    inputs = {};
    output = 0.0f;
}

void nn::Node::process(float input) { // ensure output is between [-1,1]

    //output = 0.0f;
    if (input == 0.0) {

        for (auto const &pair: inputs) {
            output += pair.first->output * pair.second;
        }
    } else{ // if this is in the first layer, we directly give it inputs
        // seperate transfer function
        // ensure output is between (-1,1). sigmoid function?
        output = input;
    }
}