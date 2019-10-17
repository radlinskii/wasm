#include "DifferentialEvolution.h"

DifferentialEvolution::DifferentialEvolution(Parameters* parameters){
    this->parameters = parameters;
    default_random_engine re;
    this->randomEngine = re;
    this->randomEngine.seed(time(NULL));
};
DifferentialEvolution::~DifferentialEvolution(){};

Population* DifferentialEvolution::getPopulation(){
    return this->population;
};
void DifferentialEvolution::setPopulation(Population* population){
    this->population = population;
};
Parameters* DifferentialEvolution::getParameters(){
    return this->parameters;
};
void DifferentialEvolution::setParameters(Parameters* parameters){
    this->parameters = parameters;
};

double DifferentialEvolution::getRandom(double min, double max) {
    uniform_real_distribution<double> unif(min, max);

    return unif(this->randomEngine);
}

void DifferentialEvolution::populate(){
    vector<Individual> individuals;

    for (int i = 0; i < this->parameters->getAgentCount(); i++) {
        vector<double> v;
        for (int j = 0; j < this->parameters->getDimensions(); j++) {
            v.push_back(this->getRandom(this->parameters->getLowerDomainBound(), this->parameters->getHigherDomainBound()));
        }
        Individual* individual = new Individual(v);
        individuals.push_back(*individual);
    }

    this->population = new Population(individuals);
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

    this->populate();

    for (Individual i : this->population->getSolutions()) {
        printf("%s\n", i.to_string().c_str());
    }

    return nullptr;
};
