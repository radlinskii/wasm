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
        Population();
        ~Population();

        vector<Individual*> getSolutions();
        void setSolutions(vector<Individual*> solutions);

        double getAverageFitness();
        double getMaximumFitness();
        double getMinimumFitness();
        double getTotalSumFitness();

        Individual* getBest();
        void evaluate(FitnessFunction* fitnessFunction);
};

#endif
