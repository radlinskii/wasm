#include "Individual.h"

using namespace std;

Individual::Individual(vector<double> elements){
    this->elements = elements;
    this->dimensions = elements.size();
};
Individual::~Individual(){};

vector<double> Individual::getElements(){
    return this->elements;
};
void Individual::setElements(vector<double> elements){
    this->elements = elements;
    this->dimensions = elements.size();
};

double Individual::getFitness(){
    return this->fitness;
};

int Individual::getDimensions(){
    return this->dimensions;
};

double Individual::evaluate(shared_ptr<FitnessFunction> f) {
    this->fitness = f->evaluate(this->elements);

    return this->fitness;
}

string Individual::toString() {
    string res = "(";
    for(double e : elements) {
        res += std::to_string(e) + string(", ");
    }

    res.erase(res.end() - 2, res.end());
    res += ")";

    return res;
}
