#include "Population.h"

Population::Population(vector<Individual> solutions){
    this->solutions = solutions;
};
Population::Population(){};
Population::~Population(){};

vector<Individual> Population::getSolutions(){
    return this->solutions;
};
void Population::setSolutions(vector<Individual> solutions){
    this->solutions = solutions;
};

double Population::getAverageFitness(){
    double sum = 0.0;

    for (Individual i : solutions) {
        sum += i.getFitness();
    }

    double average = sum / this->solutions.size();

    return average;
};
double Population::getMaximumFitness(){
    double max = -DBL_MAX;

    for (Individual i : solutions) {
        if (i.getFitness() >= max) {
            max = i.getFitness();
        }
    }

    return max;
};
double Population::getMinimumFitness(){
    double min = DBL_MAX;

    for (Individual i : solutions) {
        if (i.getFitness() <= min) {
            min = i.getFitness();
        }
    }

    return min;
};
double Population::getTotalSumFitness(){
    double sum = 0.0;

    for (Individual i : solutions) {
        sum += i.getFitness();
    }

    return sum;
};

bool comparator (Individual i, Individual j) {
    return (i.getFitness()<j.getFitness());
}

Individual* Population::getBest(){
    if (this->solutions.size() == 0) {
        return nullptr;
    }

    vector<Individual> individuals = this->solutions;

    sort(individuals.begin(), individuals.end(), comparator);

    return &individuals[0];
};

void Population::evaluate(FitnessFunction *fitnessFunction){
    for (Individual i : solutions) {
            i.evaluate(fitnessFunction);
        }
};
