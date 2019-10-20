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
        int maxNumOfIterations;
        int agentCount;
        FitnessFunction* fitnessFunction;
    public:
        Parameters(double f, double cr, int agentCount, int maxNumOfIterations, FitnessFunction* fitnessFunction);
        Parameters();
        ~Parameters();

        void ensureFBoundaries(double);

        double getF();
        void setF(double f);
        double getCR();
        void setCR(double cr);
        int getAgentCount();
        void setAgentCount(int agentCount);
        int getMaxNumOfIterations();
        void setMaxNumOfIterations(int maxNumOfIterations);
        int getDimensions();
        void setDimensions(int dimensions);
        tuple<double, double> getDomain();
        void setDomain(tuple<double, double> domain);
        FitnessFunction* getFitnessFunction();
        void setFitnessFunction(FitnessFunction* fitnessFunction);
        double getLowerDomainBound ();
        double getHigherDomainBound ();
};

#endif
