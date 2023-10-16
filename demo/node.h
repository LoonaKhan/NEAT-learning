#include <vector>
#include "random.hpp"
using Random = effolkronium::random_static;

// organize this, possibly a inputNode subclass

namespace nn {
struct Node {
    // inputs, process, output
    std::vector<std::pair<float, float>> inputs; // output of the node and its weight
    float output = 0.0f;

    Node(); // for input nodes
    Node(std::vector<Node> last_layer);

    void process(float input=0.0);

    // mutate func
};


}