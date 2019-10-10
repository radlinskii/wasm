#include "Animal.h"

Animal::Animal(std::string name)
{
    this->name = name;
}

Animal::~Animal()
{
}

const char *Animal::getName() {
    return this->name.c_str();
}
void Animal::setName(std::string name) {
    this->name = name;
}
