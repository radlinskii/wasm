#include <tuple>

#ifndef PARAMETERS_H
#define PARAMETERS_H

using namespace std;

class FitnessFunction;

class Parameters {
    private:
        double f;
        double cr;
        int iterations;
        int agentCount;
        int dimensions;
        tuple<double, double> domain;
        FitnessFunction* fitnessFunction;
    public:
        Parameters(double f, double cr, int agentCount, int iterations, int dimensions, tuple<double, double> domain, FitnessFunction* fitnessFunction);
        Parameters();
        ~Parameters();

        double getF();
        void setF(double f);
        double getCR();
        void setCR(double cr);
        int getAgentCount();
        void setAgentCount(int agentCount);
        int getIterations();
        void setIterations(int iterations);
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
