#include "DifferentialEvolution.h"

DifferentialEvolution::DifferentialEvolution(shared_ptr<Parameters> parameters){
    this->parameters = parameters;
    default_random_engine re;
    this->randomEngine = re;
    this->randomEngine.seed(time(NULL));
};
DifferentialEvolution::~DifferentialEvolution(){};

shared_ptr<Population> DifferentialEvolution::getPopulation(){
    return this->population;
};
void DifferentialEvolution::setPopulation(shared_ptr<Population> population){
    this->population = population;
};
shared_ptr<Parameters> DifferentialEvolution::getParameters(){
    return this->parameters;
};
void DifferentialEvolution::setParameters(shared_ptr<Parameters> parameters){
    this->parameters = parameters;
};

double DifferentialEvolution::getRandom(double min, double max) {
    uniform_real_distribution<double> unif(min, max);

    return unif(this->randomEngine);
}

void DifferentialEvolution::populate(){
    vector<shared_ptr<Individual>> individuals;

    for (int i = 0; i < this->parameters->getAgentCount(); i++) {
        vector<double> v;
        for (int j = 0; j < this->parameters->getDimensions(); j++) {
            v.push_back(this->getRandom(this->parameters->getLowerDomainBound(), this->parameters->getHigherDomainBound()));
        }
        shared_ptr<Individual> individual = make_shared<Individual>(v);
        individuals.push_back(individual);
    }

    this->population = make_shared<Population>(individuals);
};

void ensureBoundaries(shared_ptr<Individual> donor, double lowerBoundary, double highBoundary) {
    vector<double> correctElements;
    for (int i = 0; i < donor->getDimensions(); i++){
        if (donor->getElements()[i] < lowerBoundary) {
            correctElements.push_back(lowerBoundary);
        } else if (donor->getElements()[i] > highBoundary) {
            correctElements.push_back(highBoundary);
        } else {
            correctElements.push_back(donor->getElements()[i]);
        }
    }

    donor->setElements(correctElements);
}

shared_ptr<Individual> DifferentialEvolution::mutate(int index) {
    vector<shared_ptr<Individual>> candidates;
    vector<shared_ptr<Individual>> individuals = this->population->getSolutions();

    individuals.erase(individuals.begin() + index);

    sample(individuals.begin(), individuals.end(), candidates.begin(), 3, this->randomEngine);
    shared_ptr<Individual> c1 = candidates[0];
    shared_ptr<Individual> c2 = candidates[1];
    shared_ptr<Individual> c3 = candidates[2];

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

    shared_ptr<Individual> donor = make_shared<Individual>(mutatedElements);

    ensureBoundaries(donor, this->parameters->getLowerDomainBound(), this->parameters->getHigherDomainBound());

    return donor;
}

shared_ptr<Individual> DifferentialEvolution::recombinate(shared_ptr<Individual> current, shared_ptr<Individual> donor) {
    vector<double> recombinatedElements;
    for (int i = 0; i < this->parameters->getDimensions(); i++) {
        if (getRandom(0.0, 1.0) <= this->parameters->getCR()) {
            recombinatedElements.push_back(donor->getElements()[i]);
        } else {
            recombinatedElements.push_back(current->getElements()[i]);
        }
    }

    return make_shared<Individual>(recombinatedElements);
}

void DifferentialEvolution::select(shared_ptr<Individual> current, shared_ptr<Individual> trial) {
    double currentFitness = current->evaluate(this->parameters->getFitnessFunction());
    double trialFitness = trial->evaluate(this->parameters->getFitnessFunction());

    if (trialFitness < currentFitness) {
        current->setElements(trial->getElements());
    }
}

shared_ptr<Population> DifferentialEvolution::evaluate(){
    int generationCounter = 0;

    while(generationCounter <= this->parameters->getMaxNumOfGenerations()) {
        for (int i = 0; i < this->parameters->getAgentCount(); i++) {
            shared_ptr<Individual> current = this->population->getSolutions()[i];

            shared_ptr<Individual> donor = this->mutate(i);
            shared_ptr<Individual> trial = this->recombinate(current, donor);
            this->select(current, trial);
        }

        generationCounter++;
    }

    return this->getPopulation();
};
