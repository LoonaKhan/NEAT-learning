#include <iostream>

//#include "node.h"
#include "network.h"
using namespace nn;

int main() {
    auto nwk = Network(3,3);
    //nwk.debug();
    nwk.process({0.5, 0.4, 0.2});

    nwk.debug();
    // check if all nodes appear
    // check if all weights appear
    // try processing
}

// for some reason, we arent passing references of one layer to the next properly
// const reference??
/*
 * either set the input node var in a layer to be the output of the last layer
 * prev layer node sets output. maybe set it to the index of the node?
 * when we move to the next layer, retrieve prev layer output. pointers or index
 */