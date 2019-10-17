#include "Parameters.h"

void Parameters::ensureFBoundaries(double f) {
    if (f > 2.0 || f < 0.0) {
        printf("Parameter F should have value in range [0, 2]. set to 0.5\n");
        this->f = 0.5;
    } else {
        this->f = f;
    }
}

Parameters::Parameters(double f, double cr, int agentCount, int maxNumOfIterations, int dimensions, tuple<double, double> domain, FitnessFunction* fitnessFunction) {
    this->cr = cr;
    this->agentCount = agentCount;
    this->maxNumOfIterations = maxNumOfIterations;
    this->dimensions = dimensions;
    this->domain = domain;
    this->fitnessFunction = fitnessFunction;
    ensureFBoundaries(f);
};
Parameters::Parameters() {
    this->f = 0.5;
    this->cr = 0.9;
    this->agentCount = 20;
    this->maxNumOfIterations = 100;
};
Parameters::~Parameters(){};

double Parameters::getF(){
    return this->f;
};
void Parameters::setF(double f){
    ensureFBoundaries(f);
};

double Parameters::getCR(){
    return this->cr;
};
void Parameters::setCR(double cr){
    this->cr = cr;
};

int Parameters::getAgentCount(){
    return this->agentCount;
};
void Parameters::setAgentCount(int agentCount){
    this->agentCount = agentCount;
};

int Parameters::getMaxNumOfIterations(){
    return this->maxNumOfIterations;
};
void Parameters::setMaxNumOfIterations(int maxNumOfIterations){
    this->maxNumOfIterations = maxNumOfIterations;
};

int Parameters::getDimensions(){
    return this->dimensions;
};
void Parameters::setDimensions(int dimensions){
    this->dimensions = dimensions;
};

tuple<double, double> Parameters::getDomain(){
    return this->domain;
};
void Parameters::setDomain(tuple<double, double> domain){
    this->domain = domain;
};

FitnessFunction* Parameters::getFitnessFunction(){
    return this->fitnessFunction;
};
void Parameters::setFitnessFunction(FitnessFunction* fitnessFunction){
    this->fitnessFunction = fitnessFunction;
};

double Parameters::getLowerDomainBound (){
    return get<0>(this->domain);
};
double Parameters::getHigherDomainBound (){
    return get<1>(this->domain);
};
