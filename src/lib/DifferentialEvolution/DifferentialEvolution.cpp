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
    vector<Individual*> individuals;

    for (int i = 0; i < this->parameters->getAgentCount(); i++) {
        vector<double> v;
        for (int j = 0; j < this->parameters->getDimensions(); j++) {
            v.push_back(this->getRandom(this->parameters->getLowerDomainBound(), this->parameters->getHigherDomainBound()));
        }
        Individual* individual = new Individual(v);
        individuals.push_back(individual);
    }

    this->population = new Population(individuals);
};

Individual ensureBoundaries(Individual donor, double lowerBoundary, double highBoundary) {
    vector<double> correctElements;
    for (int i = 0; i < donor.getDimensions(); i++){
        if (donor.getElements()[i] < lowerBoundary) {
            correctElements.push_back(lowerBoundary);
        } else if (donor.getElements()[i] > highBoundary) {
            correctElements.push_back(highBoundary);
        } else {
            correctElements.push_back(donor.getElements()[i]);
        }
    }

    donor.setElements(correctElements);

    return donor;
}

Individual DifferentialEvolution::mutate(int index) {
    vector<Individual*> candidates;
    vector<Individual*> individuals = this->population->getSolutions();
    Individual* current = individuals[index];

    individuals.erase(individuals.begin() + index);

    sample(individuals.begin(), individuals.end(), candidates.begin(), 3, this->randomEngine);
    Individual* c1 = candidates[0];
    Individual* c2 = candidates[1];
    Individual* c3 = candidates[2];

    // (c2−c3)
    vector<double> diff;
    for (int i = 0; i < this->parameters->getDimensions(); i++) {
        diff.push_back(c2->getElements()[i] - c3->getElements()[i]);
    }

    // v=c1+F*(c2−c3)
    vector<double> mutatedElements;
    for (int i = 0; i < this->parameters->getDimensions(); i++) {
        mutatedElements.push_back(c1->getElements()[i] + (this->getParameters()->getF() * diff[i]));
    }

    Individual* donor = new Individual(mutatedElements);

    return ensureBoundaries(*donor, this->parameters->getLowerDomainBound(), this->parameters->getHigherDomainBound());
}

Individual DifferentialEvolution::recombinate(Individual current, Individual donor) {
    vector<double> recombinatedElements;
    for (int i = 0; i < this->parameters->getDimensions(); i++) {
        if (getRandom(0.0, 1.0) <= this->parameters->getCR()) {
            printf("recombinated\n");
            recombinatedElements.push_back(donor.getElements()[i]);
        } else {
            recombinatedElements.push_back(current.getElements()[i]);
        }
    }
    Individual* recombinated = new Individual(recombinatedElements);

    current.setElements(recombinatedElements);

    return current;
}

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

    while(this->parameters->getMaxNumOfIterations() + 1) {
        for (int i = 0; i < this->parameters->getAgentCount(); i++) {
            Individual* current = this->population->getSolutions()[i];
            Individual donor = this->mutate(i);

            Individual recombinated = this->recombinate(*current, donor);
            printf("original from population: %s | donor: %s\n", current->to_string().c_str(), donor.to_string().c_str());

            current->setElements(recombinated.getElements());
            printf("recombinated: %s | original from population: %s\n", current->to_string().c_str(), this->population->getSolutions()[i]->to_string().c_str());
        }

        this->parameters->setMaxNumOfIterations(this->parameters->getMaxNumOfIterations() - 1);
    }

    return nullptr;
};
