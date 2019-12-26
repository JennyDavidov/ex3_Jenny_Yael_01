//
// Created by jenny on 19/12/2019.
//

#include "Sim.h"
#include <string>

using namespace std;

int Sim::execute(string *str, Interpreter *interpreter) {
    int index;
    string key;
    int dir;
    //take the var name from the template var NAME -> sim(ADDRESS)
    (str) += 1;
    //if copying existing varaible to a local variable
    if ((*str).find("=") != string::npos) {
        //separate key name
        index = (*str).find("=");
        key = (*str).substr(0, index);
        //deleting spaces if exists
        (key).replace((key).find(" "), 1, "");
        string str1 = (*str).substr(index + 1);
        (str1).replace((str1).find(" "), 1, "");
        //finding existing variable
        Variable* copy = flyMap.find(str1)->second;
        //copying details of existing variable
        dir = copy->getDirection();
        string sim = copy->getName();
        double value = copy->getValue();
        //creating new variable
        Variable* var = new Variable(sim, value);
        var->setDirection(dir);
        flyMap.insert(pair<string, Variable *>(key, reinterpret_cast<Variable *const>(&var)));
        return 2;
    }
    //defining variable to flyMap
    else {
        key = (*str);
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
}

Sim::Sim() {}

