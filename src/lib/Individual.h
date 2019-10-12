#include <string>

class Individual
{
private:
    std::string name;
public:
    Individual(std::string name = 0);
    ~Individual();
    const char *getName();
    void setName(std::string name);
};
