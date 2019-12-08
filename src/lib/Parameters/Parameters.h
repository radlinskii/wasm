#include <tuple>
#include <stdio.h>

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "../FitnessFunctions/FitnessFunction.cpp"

using namespace std;

class Parameters {
    private:
        double f;
        double cr;
        int maxNumOfGenerations;
        int agentCount;
        shared_ptr<FitnessFunction> fitnessFunction;
    public:
        Parameters(double f, double cr, int agentCount, int maxNumOfGenerations, shared_ptr<FitnessFunction> fitnessFunction);
        Parameters();
        ~Parameters();

        void ensureFBoundaries(double);

        double getF();
        void setF(double f);
        double getCR();
        void setCR(double cr);
        int getPopulationLength();
        void setPopulationLength(int agentCount);
        int getMaxNumOfGenerations();
        void setMaxNumOfGenerations(int maxNumOfGenerations);
        int getDimensions();
        void setDimensions(int dimensions);
        tuple<double, double> getDomain();
        void setDomain(tuple<double, double> domain);
        shared_ptr<FitnessFunction> getFitnessFunction();
        void setFitnessFunction(shared_ptr<FitnessFunction> fitnessFunction);
        double getLowerDomainBound ();
        double getHigherDomainBound ();
};

#endif
