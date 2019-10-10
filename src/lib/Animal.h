#include <string>

class Animal
{
private:
    std::string name;
public:
    Animal(std::string name = 0);
    ~Animal();
    const char *getName();
    void setName(std::string name);
};
