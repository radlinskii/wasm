#include "Population.h"

Population::Population(vector<Individual*> solutions){
    this->solutions = solutions;
};


Population::Population(vector<vector<double>> vectors) {
    for(int i = 0; i < vectors.size(); i++) {
        this->solutions.push_back(new Individual(vectors[i]));
    }
}

Population::Population(){};
Population::~Population(){};

vector<Individual*> Population::getSolutions(){
    return this->solutions;
};
void Population::setSolutions(vector<Individual*> solutions){
    this->solutions = solutions;
};


vector<vector<double>> Population::toVectors() {
    vector<vector<double>> vector2d;
    for (int i = 0; i < this->getSolutions().size(); i++) {
        vector2d.push_back(this->getSolutions()[i]->getElements());
    }

    return vector2d;
}

double Population::getAverageFitness(){
    double sum = 0.0;

    for (Individual* i : solutions) {
        sum += i->getFitness();
    }

    double average = sum / this->solutions.size();

    return average;
};
double Population::getMaximumFitness(){
    double max = -DBL_MAX;

    for (Individual* i : solutions) {
        if (i->getFitness() >= max) {
            max = i->getFitness();
        }
    }

    return max;
};
double Population::getMinimumFitness(){
    double min = DBL_MAX;

    for (Individual* i : solutions) {
        if (i->getFitness() <= min) {
            min = i->getFitness();
        }
    }

    return min;
};
double Population::getTotalSumFitness(){
    double sum = 0.0;

    for (Individual* i : solutions) {
        sum += i->getFitness();
    }

    return sum;
};

bool comparator (Individual* i, Individual* j) {
    return (i->getFitness()<j->getFitness());
}

Individual* Population::getBest(){
    if (this->solutions.size() == 0) {
        return nullptr;
    }

    vector<Individual*> individuals = this->solutions;

    sort(individuals.begin(), individuals.end(), comparator);

    return individuals[0];
};

void Population::evaluate(FitnessFunction* fitnessFunction){
    for (Individual* i : solutions) {
        i->evaluate(fitnessFunction);
    }
};
