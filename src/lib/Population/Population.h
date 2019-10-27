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
        vector<Individual*> solutions;
    public:
        Population(vector<Individual*> solutions);
        Population(vector<vector<double>> vectors);
        Population();
        ~Population();

        vector<Individual*> getSolutions();
        void setSolutions(vector<Individual*> solutions);

        vector<vector<double>> toVectors();

        double getAverageFitness();
        double getMaximumFitness();
        double getMinimumFitness();
        double getTotalSumFitness();

        Individual* getBest();
        void evaluate(FitnessFunction* fitnessFunction);
};

#endif
