#include <string>
#include <list>

using namespace std;

class Individual
{
private:
    double fitness;
    int dimensions;
    list<double> elements;
public:
    Individual(list<double> elements);
    ~Individual();

    list<double> getElements();
    void setElements(list<double> elements);

    double getFitness();

    int getDimensions();

    double evaluate(double evalFunc(Individual*, int));

    string to_string();
};
