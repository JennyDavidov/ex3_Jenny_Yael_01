//
// Created by jenny on 19/12/2019.
//

#include "Sim.h"
#include "Assignment.h"
#include <string>
#include <iostream>
#include <mutex>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;
extern mutex mtx;

int Sim::execute(string *str, Interpreter *interpreter) {
    int index;
    string key;
    int dir;
    //if copying existing variable to a local variable
    if ((*str).find("=") != string::npos) {
        //separate the name of existing variable
        index = (*str).find("=");
        key = (*str).substr(0, index);
        //deleting spaces from key if exists
        (key).replace((key).find(" "), 1, "");
        string str1 = (*str).substr(index + 1);
        (str1).replace((str1).find(" "), 1, "");
        //finding existing variable
        auto copy = flyMap.find(str1)->second;
        //copying value of existing variable
        string sim = "";
        double value = copy->getValue();
        //creating new variable
        Variable* var = new Variable(sim, value);
        //inserting variable to the flyMap
        flyMap.insert(pair<string, Variable *>(key, reinterpret_cast<Variable *const>(&var)));
        string value1 = to_string(value);
        string strToInterpreter = key + "=" + value1;
        //creating variable in variables map of interpreter
        if(mtx.try_lock()) {
            interpreter->setVariables(strToInterpreter);
            mtx.unlock();
        }
        return 2;
    }
    //defining variable to flyMap
    else {
        key = (*str);
        (str) += 1;
        string direction = *str;
        //setting direction of variable, 0 if it's updated from us or 1 from simulator
        if (direction == "<-") {
            dir = 1;
        } else if (direction == "->") {
            dir = 0;
        }
        //passing the word "sim"
        (str) += 2;
        string findSim = (*str);
        //updating in the existing variable (that was created in simulatorMap) the direction
        simulatorMap.find(findSim)->second->setDirection(dir);
        //inserting the existing variable object and it's name to flyMap
        flyMap.insert(pair<string, Variable *>(key, simulatorMap.find(findSim)->second));
        string value = to_string(simulatorMap.find(findSim)->second->getValue());
        string strToInterpreter = key + "=" + value;
        if (mtx.try_lock()) {
            //creating variable in variables map of interpreter
            interpreter->setVariables(strToInterpreter);
            mtx.unlock();
        }
        return 5;
    }
}

Sim::Sim() {}

