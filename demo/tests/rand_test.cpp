//
// Created by loona on 10/11/23.
//
#include "random.hpp"
#include "stdio.h"

using Random = effolkronium::random_static;

int main() {
    Random::seed(100);

    for (int i=0; i<5; i++){
        printf("num: %d\n", Random::get(1,100));
    }
    printf("\n");

    Random::seed(100);
    for (int i=0; i<5; i++){
        printf("num: %d\n", Random::get(1,100));
    }
}