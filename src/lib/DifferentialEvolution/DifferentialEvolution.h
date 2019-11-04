#include <random>

#ifndef DIFFERENTIAL_EVOLUTION_H
#define DIFFERENTIAL_EVOLUTION_H

#include "../Population/Population.h"
#include "../Parameters/Parameters.h"

using namespace std;

class DifferentialEvolution {
    private:
        shared_ptr<Population> population;
        shared_ptr<Parameters> parameters;
        default_random_engine  randomEngine;

        double getRandom(double, double);
        void populate();
        shared_ptr<Individual> mutate(int);
        shared_ptr<Individual> recombinate(shared_ptr<Individual>, shared_ptr<Individual>);
        void select(shared_ptr<Individual>, shared_ptr<Individual>);
    public:
        DifferentialEvolution(shared_ptr<Parameters> parameters);
        ~DifferentialEvolution();

        shared_ptr<Population> getPopulation();
        void setPopulation(shared_ptr<Population> population);
        shared_ptr<Parameters> getParameters();
        void setParameters(shared_ptr<Parameters> parameters);

        shared_ptr<Population> evaluate();
};

#endif
