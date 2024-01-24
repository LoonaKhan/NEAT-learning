#include "node.h"

nn::Node::Node(std::vector<Node> &last_layer) {

    //num_inputs = last_layer.size();

    for (auto const& node : last_layer)
        inputs.push_back(&node);

    for (int i=0; i<(int)inputs.size(); i++){ // assigns weights
        weights.push_back(Random::get(-1.0, 1.0));
    }
    weights.push_back(Random::get(0.0, 1.0)); // last weight is the threshold
    output = 0.0f;
}



nn::Node::Node(){
    inputs = {};
    output = 0.0f;
}

void nn::Node::activate(float input) {

    output = 0.0f;
    output = input;
}

void nn::Node::activate() {
    output = 0.0f;
    // todo: simplify this. use matrices?
    for (int i=0; i < (int)inputs.size(); i++) {
        output += inputs[i]->output * weights[i];
    }
    output -= weights[weights.size()-1];//output - threshold
    output = 1/(1+exp(-output));// sigmoid
}