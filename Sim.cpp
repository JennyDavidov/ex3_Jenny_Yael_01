//
// Created by jenny on 19/12/2019.
//

#include "Sim.h"
#include <string>

using namespace std;

int Sim::execute(string *str, Interpreter *interpreter) {
    //take the var name from the template var NAME -> sim(ADDRESS)
    (str) += 1;
    string key = (*str);
    int dir;
    (str) += 1;
    string direction = *str;
    if (direction == "<-") {
        dir = 1;
    } else if (direction == "->") {
        dir = 0;
    }
    (str) += 2;
    string findSim = (*str);
    Variable *obj = simulatorMap.find(findSim)->second;
    obj->setDirection(dir);
    flyMap.insert(pair<string, Variable *>(key, reinterpret_cast<Variable *const>(&obj)));
    return 5;
}

Sim::Sim() {}

