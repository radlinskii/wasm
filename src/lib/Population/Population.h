#include <vector>
#include <algorithm>
#include <float.h>

#ifndef POPULATION_H
#define POPULATION_H

#include "../Individual/Individual.h"

class FitnessFunction;

using namespace std;

class Population {
    private:
        vector<shared_ptr<Individual>> solutions;
    public:
        Population(vector<shared_ptr<Individual>> solutions);
        Population(vector<vector<double>> vectors);
        Population();
        ~Population();

        vector<shared_ptr<Individual>> getSolutions();
        void setSolutions(vector<shared_ptr<Individual>> solutions);

        vector<vector<double>> toVectors();

        double getAverageFitness();
        double getMaximumFitness();
        double getMinimumFitness();
        double getTotalSumFitness();

        shared_ptr<Individual> getBest();
        void evaluate(shared_ptr<FitnessFunction> fitnessFunction);
};

#endif
