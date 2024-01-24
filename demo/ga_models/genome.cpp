//
// Created by loona on 19/12/23.
//

#include "genome.h"


Genome::Genome( std::vector<std::vector<nn::Node>> network, int inputs, int outputs, int layer_size, int hidden_layers, int fitness)
:inputs(inputs), outputs(outputs), layer_size(layer_size), hidden_layers(hidden_layers), fitness(fitness){
    for (const auto& l : network){
        for (auto n : l){
            for (int i=0; i<n.inputs.size()+1; i++)
                if (n.weights.size() != 0) genome.push_back(n.weights[i]);
        }
    }
}

Genome::Genome() :fitness(0){}

void Genome::Mutate() {
    float mut_rate = config["mut_rate"];
    float mut_amt = config["mut_amt"];

    for (auto &chromie : genome){
        if (Random::get(0.0, 1.0) < mut_rate){
            chromie += Random::get({-1,1}) * mut_amt;
        }
    }
}

std::pair<Genome, Genome> Genome::Crossover(std::pair<Genome, Genome> parents) {
    float crossover_rate = config["crossover_rate"];

    std::pair<Genome, Genome> children;
    children.first.inputs = parents.first.inputs;
    children.first.outputs = parents.first.outputs;
    children.first.layer_size = parents.first.layer_size;
    children.first.hidden_layers = parents.first.hidden_layers;

    children.second.inputs = parents.second.inputs;
    children.second.outputs = parents.second.outputs;
    children.second.layer_size = parents.second.layer_size;
    children.second.hidden_layers = parents.second.hidden_layers;


    if (Random::get(0.0,1.0) < crossover_rate){
        int index = Random::get(0, (int)parents.first.genome.size()-1); // get the index

        for (int i=0; i< (int)parents.first.genome.size(); i++){
            if (i < index){
                children.first.genome.push_back(parents.first.genome[i]);
                children.second.genome.push_back(parents.second.genome[i]);
            } else {
                children.first.genome.push_back(parents.second.genome[i]);
                children.second.genome.push_back(parents.first.genome[i]);
            }
        }
    } else {
        children = parents;
    }

    return children;
}

std::pair<Genome, Genome> Genome::RouletteSelection(std::vector<Genome> population) {
    // find total fitness
    int total_fitness=0;
    for (auto genome : population){
        total_fitness+= genome.fitness;
    }

    std::pair<Genome, Genome> parents;
    float slice;
    int total=0;
    for (int i=0; i < 2; i++) {
        slice= Random::get(0.0,1.0) * total_fitness;
        total = 0;

        for (auto genome : population) {
            total += genome.fitness;
            if (total > slice) {
                if (i==0){
                    parents.first = genome;
                } else {
                    parents.second = genome;
                }
                break;
            }
        }
    }

    return parents;
}