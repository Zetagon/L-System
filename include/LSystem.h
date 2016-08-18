#ifndef LSYSTEM_H
#define LSYSTEM_H
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

class LSystem
{
    public:
        LSystem(std::string filename );
        virtual ~LSystem();
        std::vector<char> readFile(std::string fileName);
        std::vector<char> GenerateString(int iterations);
        void CreateGrammar(std::vector<char> ch);
        void Render(std::vector<char> ch);
    protected:
    std::vector<char> constants;
    std::vector<std::vector<char>> rules;
    double angle;
    const double PI = acos(-1);
    private:
};

#endif // LSYSTEM_H
