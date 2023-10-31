#include "node.h"

nn::Node::Node(std::vector<Node> &last_layer) {
    for (auto const& node : last_layer){
        // for each node, assign a weight to it and append to inputs
        std::pair<const Node*, float> p;
        p.first = &node;
        p.second = Random::get(-1.0, 1.0);
        inputs.push_back(p);
    }
    output = 0.0f;
    threshold = Random::get(0.0,1.0); // maybe based on the size of the network? todo: optimal ways to determine threshold
}

nn::Node::Node(){
    inputs = {};
    output = 0.0f;
}

void nn::Node::activate(float input) { // ensure output is between [-1,1]

    output = 0.0f;
    if (input == 0.0) {

        // todo: simplify this. use matrices?
        for (auto const &pair: inputs) {
            output += pair.first->output * pair.second;
        }
        output -= threshold;//output - threshold
        output = 1/(1+exp(-output));// sigmoid

    } else{ // if this is in the first layer, we directly give it inputs
        // seperate transfer function
        // ensure output is between (-1,1). sigmoid function?
        output = input;
    }
}

void nn::Node::mutate() {
    // cycles through a nodes weights and has a chance of mutating.
    // mutations should be quite rare, but impactful
    for (auto& [_, w] : this->inputs) {
        if (Random::get(1,100) == 1){ // maybe rarer?
            w += Random ::get(-0.5, 0.5);
        }
    }
}