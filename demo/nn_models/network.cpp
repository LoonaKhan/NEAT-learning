//
// Created by loona on 16/10/23.
//

#include "network.h"


nn::Network::Network(int inputs, int outputs, int layer_size, int hidden_layers)
:inputs(inputs), outputs(outputs), layer_size(layer_size), hidden_layers(hidden_layers) {
    // creates a neural network

    std::vector<Node> flayer, llayer;
    for (int inp=0; inp < inputs;inp++){
        Node n = Node();
        flayer.push_back(n);
    }
    nodes.push_back(flayer);

    for (int i=0; i < hidden_layers; i++){
        std::vector<Node> layer;
        for (int j=0; j<layer_size; j++){
            Node n = Node(nodes[i]);
            layer.push_back(n);
        }
        nodes.push_back(layer);
    }
    for (int out=0; out<outputs; out++){
        Node n = Node(nodes[nodes.size()-1]);
        llayer.push_back(n);
    }
    nodes.push_back(llayer);
}

nn::Network::Network(Genome g)
:inputs(g.inputs), outputs(g.outputs), layer_size(g.layer_size), hidden_layers(g.hidden_layers){

    // todo: use the topology to insert Genome weights into the nodes
    printf("chromosme: ");
    for (auto chromie : g.genome) {
        printf("%f ", chromie);
    }
    printf("\n");

    std::vector<Node> flayer, llayer;
    for (int inp=0; inp < inputs;inp++){
        Node n = Node();
        flayer.push_back(n);
    }
    nodes.push_back(flayer);

    for (int i=0; i < hidden_layers; i++){
        std::vector<Node> layer;
        for (int j=0; j<layer_size; j++){
            Node n = Node(nodes[i]);

            int w=0;
            for (; w < n.weights.size(); w++){
                n.weights[w] = g.genome[w];
            }
            // remove indices up until w
            Genome ng;
            for (int k=0; k < g.genome.size(); k++){
                if (k > w){
                    ng.genome.push_back(g.genome[k]);
                }
            }
            ng.inputs = g.inputs;
            ng.outputs = g.outputs;
            ng.layer_size = g.layer_size;
            ng.hidden_layers = g.hidden_layers;
            g = ng;

            layer.push_back(n);
        }
        nodes.push_back(layer);
    }
    for (int out=0; out<outputs; out++){
        Node n = Node(nodes[nodes.size()-1]);

        int w=0;
        for (; w < n.weights.size(); w++){
            n.weights[w] = g.genome[w];
        }
        // remove indices up until w
        Genome ng;
        for (int k=0; k < g.genome.size(); k++){
            if (k > w){
                ng.genome.push_back(g.genome[k]);
            }
        }
        ng.inputs = g.inputs;
        ng.outputs = g.outputs;
        ng.layer_size = g.layer_size;
        ng.hidden_layers = g.hidden_layers;
        g = ng;

        llayer.push_back(n);
    }
    nodes.push_back(llayer);
}

nn::Network::Network(){}

std::vector<nn::Node> nn::Network::process(std::vector<float> inputs) {
    int i =0;
    for (; i < nodes.size(); i++){

        for (int j=0; j< nodes[i].size(); j++){

            if (i == 0) { // if its in the first layer, pass in the inputs
                nodes[i][j].activate(inputs[j]);
            } else {
                nodes[i][j].activate();
            }

            //printf("[%d, %d]: %f\n",i,j, nodes[i][j].output);

        }
    }

    return nodes[nodes.end()-nodes.begin()-1];
}

void nn::Network::debug(bool weights_only) {
    // prints debug info
    // arrangement of nodes as coordinates and their weights
     for (int layer = 0; layer< nodes.size(); layer++) {
         printf("Layer %d: ", layer);
         for (int node=0; node < nodes[layer].size(); node++) {
            printf("{[%d,%d] ", layer, node);
            int i=0;
            for (; i < nodes[layer][node].inputs.size(); i++){
                if (!weights_only){
                    printf("(%f,%f)", nodes[layer][node].inputs[i], nodes[layer][node].weights[i]);
                }
                else
                    printf("(%f)", nodes[layer][node].weights[i]);
            }
             printf("bias: (%f) }  ", nodes[layer][node].weights[i+1]);
         }
         printf("\n");
     }
}