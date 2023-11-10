#include <vector>
#include "../random.hpp"

using Random = effolkronium::random_static;

// organize this, possibly a inputNode subclass

namespace nn {
struct Node {
    // inputs, activate, output
    std::vector<std::pair<const Node*, float>> inputs; // output of the node and its weight
    float output ;
    float threshold;

    Node(); // for input nodes
    Node(std::vector<Node> &last_layer);

    void activate(float input=0.0);

    // mutate func
    void mutate();
};


}