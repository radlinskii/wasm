#include "Individual.h"

using namespace std;

Individual::Individual(list<double> elements){
    this->elements = elements;
    this->dimensions = elements.size();
};
Individual::~Individual(){};

list<double> Individual::getElements(){
    return this->elements;
};
void Individual::setElements(list<double> elements){
    this->elements = elements;
    this->dimensions = elements.size();
};

double Individual::getFitness(){
    return this->fitness;
};

int Individual::getDimensions(){
    return this->dimensions;
};

double Individual::evaluate(double evalFunc(Individual*, int)) {
    this->fitness = evalFunc(this, this->dimensions);

    return this->fitness;
}

string Individual::to_string() {
    string res;
    for(double e : elements) {
        res += std::to_string(e) + string(", ");
    }

    res.erase(res.end() - 2, res.end());

    return res;
}
