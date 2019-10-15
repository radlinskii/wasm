#ifndef DIFFERENTIAL_EVOLUTION_H
#define DIFFERENTIAL_EVOLUTION_H

#include "../Population/Population.h"
#include "../Parameters/Parameters.h"

using namespace std;

class DifferentialEvolution {
    private:
        Population population;
        Parameters parameters;
    public:
        DifferentialEvolution(Population population, Parameters parameters);
        ~DifferentialEvolution();

        Population getPopulation();
        void setPopulation(Population population);
        Parameters getParameters();
        void setParameters(Parameters parameters);

        Individual* evaluate();
};

#endif
