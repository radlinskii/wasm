#include "Individual.h"

Individual::Individual(std::string name)
{
    this->name = name;
}

Individual::~Individual()
{
}

const char *Individual::getName() {
    return this->name.c_str();
}
void Individual::setName(std::string name) {
    this->name = name;
}
