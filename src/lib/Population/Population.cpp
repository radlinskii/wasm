#include "Population.h"

Population::Population(vector<shared_ptr<Individual>> solutions){
    this->solutions = solutions;
};


Population::Population(vector<vector<double>> vectors) {
    for(int i = 0; i < vectors.size(); i++) {
        this->solutions.push_back(make_shared<Individual>(vectors[i]));
    }
}

Population::Population(){};
Population::~Population(){};

vector<shared_ptr<Individual>> Population::getSolutions(){
    return this->solutions;
};
void Population::setSolutions(vector<shared_ptr<Individual>> solutions){
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

    for (shared_ptr<Individual> i : solutions) {
        sum += i->getFitness();
    }

    double average = sum / this->solutions.size();

    return average;
};
double Population::getMaximumFitness(){
    double max = -DBL_MAX;

    for (shared_ptr<Individual> i : solutions) {
        if (i->getFitness() >= max) {
            max = i->getFitness();
        }
    }

    return max;
};
double Population::getMinimumFitness(){
    double min = DBL_MAX;

    for (shared_ptr<Individual> i : solutions) {
        if (i->getFitness() <= min) {
            min = i->getFitness();
        }
    }

    return min;
};
double Population::getTotalSumFitness(){
    double sum = 0.0;

    for (shared_ptr<Individual> i : solutions) {
        sum += i->getFitness();
    }

    return sum;
};

bool comparator (shared_ptr<Individual> i, shared_ptr<Individual> j) {
    return (i->getFitness()<j->getFitness());
}

shared_ptr<Individual> Population::getBest(){
    if (this->solutions.size() == 0) {
        return nullptr;
    }

    vector<shared_ptr<Individual>> individuals = this->solutions;

    sort(individuals.begin(), individuals.end(), comparator);

    return individuals[0];
};

void Population::evaluate(shared_ptr<FitnessFunction> fitnessFunction){
    for (shared_ptr<Individual> i : solutions) {
        i->evaluate(fitnessFunction);
    }
};
