#include "DifferentialEvolution.h"

DifferentialEvolution::DifferentialEvolution(Population population, Parameters parameters){
    this->population = population;
    this->parameters = parameters;
};
DifferentialEvolution::~DifferentialEvolution(){};

Population DifferentialEvolution::getPopulation(){
    return this->population;
};
void DifferentialEvolution::setPopulation(Population population){
    this->population = population;
};
Parameters DifferentialEvolution::getParameters(){
    return this->parameters;};
void DifferentialEvolution::setParameters(Parameters parameters){
    this->parameters = parameters;
};

Individual* DifferentialEvolution::evaluate(){
    /*
    1) Initialize a random population of individuals throughout the search space.

    2) while iter <= max num of generations

        3) cycle through each individual in the population

            3.A) perform mutation

            3.B) perform recombination ("crossover" in GA lingo)

            3.C) perform selection

        4) if stopping criterion has been met:
                exit and return best individual

            else:
                iter = iter + 1
                go back to step #3
    */

    return nullptr;
};
