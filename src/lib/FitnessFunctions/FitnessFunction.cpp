#include <cmath>
#include <vector>

using namespace std;

#ifndef FITNESS_FUNCTION_H
#define FITNESS_FUNCTION_H

class FitnessFunction {
    protected:
        int dimensions;
        tuple<double, double> domain;
    public:
        FitnessFunction(){};
        FitnessFunction(int dimensions, tuple<double, double> domain) {
            this->dimensions = dimensions;
            this->domain = domain;
        }
        ~FitnessFunction(){};

        virtual double evaluate(vector<double>) = 0;

        int getDimensions() {
            return this->dimensions;
        }

        void setDimensions(int dimensions) {
            this->dimensions = dimensions;
        }

        tuple<double, double> getDomain() {
            return this->domain;
        }

        void setDomain(tuple<double, double> domain) {
            this->domain = domain;
        }

        double getLowerDomainBound (){
            return get<0>(this->domain);
        };
        double getHigherDomainBound (){
            return get<1>(this->domain);
        };
};

#endif
