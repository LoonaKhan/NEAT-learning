#include <iostream>

//#include "node.h"
#include "network.h"
//#include "fmt/printf.h"
#include <stdio.h>
using namespace nn;

int main() {
    std::vector<float> inputs = {0.5, 0.4, 0.2};
    printf("inputs:\n");
    for (auto const& input : inputs)
        printf("%f ", input);
    printf("\n\n");

    auto nwk = Network(3,3);

    nwk.process(inputs);
    nwk.debug();

    printf("\noutputs:\n");
    auto output = nwk.nodes[nwk.nodes.size()-1];
    for (auto node : output)
        printf("%f ",node.output);
    printf("\n");
}