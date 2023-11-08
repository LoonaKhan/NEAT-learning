#include <iostream>

//#include "node.h"
#include "../nn_models/network.h"
//#include "fmt/printf.h"
#include <stdio.h>
using namespace nn;

void processTest(){
    std::vector<float> inputs = {698, -35, 698, -35};
    printf("inputs:\n");
    for (auto const& input : inputs)
        printf("%f ", input);
    printf("\n\n");

    auto nwk = Network(4,2,3,5);

    auto output = nwk.process(inputs);
    nwk.debug();

    printf("\noutputs:\n");
    //auto output = nwk.nodes[nwk.nodes.size()-1];
    for (auto node : output)
        printf("%f ",node.output);
    printf("\n");
}

void mutateTest(){
    auto nwk = Network(2,2,3,3);
    nwk.debug();
    printf("\n");
    nwk.mutate();
    nwk.debug();
}

int main() {
    //mutateTest();
    while (true){ processTest(); }
}