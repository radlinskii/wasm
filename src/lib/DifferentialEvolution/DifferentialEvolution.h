#include <random>

#ifndef DIFFERENTIAL_EVOLUTION_H
#define DIFFERENTIAL_EVOLUTION_H

#include "../Population/Population.h"
#include "../Parameters/Parameters.h"

using namespace std;

class DifferentialEvolution {
    private:
        Population* population;
        Parameters* parameters;
        default_random_engine  randomEngine;
    public:
        DifferentialEvolution(Parameters* parameters);
        ~DifferentialEvolution();

        Population* getPopulation();
        void setPopulation(Population* population);
        Parameters* getParameters();
        void setParameters(Parameters* parameters);

        double getRandom(double, double);
        void populate();
        Individual* evaluate();
};

#endif
