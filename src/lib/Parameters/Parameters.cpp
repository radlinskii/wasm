#include "Parameters.h"

Parameters::Parameters(double f, double cr, int agentCount, int iterations, int dimensions, tuple<double, double> domain, FitnessFunction *fitnessFunction) {
    this->f = f;
    this->cr = cr;
    this->agentCount = agentCount;
    this->iterations = iterations;
    this->dimensions = dimensions;
    this->domain = domain;
    this->fitnessFunction = fitnessFunction;
};
Parameters::Parameters() {
    this->f = 0.5;
    this->cr = 0.9;
    this->agentCount = 20;
    this->iterations = 100;
};
Parameters::~Parameters(){};

double Parameters::getF(){
    return this->f;
};
void Parameters::setF(double f){
    this->f = f;
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

int Parameters::getIterations(){
    return this->iterations;
};
void Parameters::setIterations(int iterations){
    this->iterations = iterations;
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

FitnessFunction *Parameters::getFitnessFunction(){
    return this->fitnessFunction;
};
void Parameters::setFitnessFunction(FitnessFunction *fitnessFunction){
    this->fitnessFunction = fitnessFunction;
};
