//
// Created by loona on 19/12/23.
//


#pragma once

#include "vector"
#include "../nn_models/node.h"
#include "../config/config.h"


class Genome {


public:

    int inputs, outputs, layer_size, hidden_layers; // topology
    int fitness;

    std::vector<float> genome;

    Genome( std::vector<std::vector<nn::Node>> network, int inputs, int outputs, int layer_size, int hidden_layers, int fitness);

    Genome();

    static std::pair<Genome, Genome> RouletteSelection(std::vector<Genome> population);

    static std::pair<Genome, Genome> Crossover(std::pair<Genome, Genome> parents);

    void Mutate();
};
