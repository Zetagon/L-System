#include "LSystem.h"
#include "Turtle.h"
#include <iostream>
LSystem::LSystem(std::string filename )
{
    //ctor
    std::vector<char> temp;
    rules.push_back(temp);
    temp = readFile(filename);
    CreateGrammar(temp);
    temp = GenerateString(6);
    Render(temp);
}

LSystem::~LSystem()
{
    //dtor
}

std::vector<char> LSystem::readFile(std::string fileName){
    std::vector<char> ch;
    char c;
    std::fstream fin(fileName.c_str(), std::fstream::in);
    while(fin >> c){
        ch.push_back(c);
        std::cout << c;
    }
    return ch;
}

void LSystem::CreateGrammar(std::vector<char> ch){

    std::vector<char> temp;
    int a = 0;
    for(int i = 0; ch.at(i) != '_'; i++){
        temp.push_back(ch.at(i));
        a = i;
    }
    std::string sAngle(temp.begin(), temp.end());
    angle = std::stoi(sAngle);
    angle = angle * PI / 180;
    for(int i = a + 2; ch.at(i) != '_'; i ++){
        constants.push_back(ch.at(i));
        a = i;
    }
    int n = 0;
    for (int b = a +2; b < ch.size(); b++){
        if(ch.at(b) != '_'){
            rules.at(n).push_back(ch.at(b));
        }
        else{
            n++;
            std::vector<char> temp;
            rules.push_back(temp);
        }
    }
}

std::vector<char> LSystem::GenerateString(int iterations){
    std::vector<char> returnVector = constants;
    std::vector<char> tempV;
    for(int i = 0; i < iterations; i++){
        tempV.clear();
        for(int a = 0; a < returnVector.size() ; a++){
            bool foundRule = false;
            for(int b = 0; b < rules.size(); b++){
                if(returnVector.at(a) == rules.at(b).at(0)){
                    for(int c = 2; c < rules.at(b).size(); c++){
                        tempV.push_back(rules.at(b).at(c));
                    }
                    foundRule = true;
                }
            }
            if(!foundRule){
                tempV.push_back(returnVector.at(a));
            }
        }
        returnVector = tempV;
    }
    return returnVector;
}

void LSystem::Render(std::vector<char> ch){
    float length = 500;
    Turtle turtle(400,650);
    turtle.PenDown();
    std::cout << "\n";
    for(int i = 0; i < ch.size(); i++){
    std::cout << ch.at(i);
        switch(ch.at(i)){
            case 'F':
                turtle.PenDown();
                if(round(length) == 0)
                    turtle.Forward(1);
                else
                    turtle.Forward(round(length));
//                turtle.Render();
            break;
            case '+':
                turtle.Turn(angle);
            break;
            case '-':
                turtle.Turn(-angle);
            break;
            case '[':
                turtle.SavePoint();
            break;
            case ']':
                turtle.ReturnToSavedPoint();
            break;
            case'!':
                std::vector<char> temp;
                for(int a = i + 1; ch.at(a) != '?' && a < ch.size(); a++){
                    temp.push_back(ch.at(a));
                }
                std::string tempS(temp.begin(),temp.end());
                float f = atof(tempS.c_str());
                length = length * f;

//                std::cout << "f is " <<tempS;
            break;
        }

    }

        turtle.Render();
    char c;
    std::cin >>c;
}
