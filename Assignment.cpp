//
// Created by jenny on 25/12/2019.
//

#include "Assignment.h"
#include <string>
#include <cstring>
#include <mutex>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;
extern queue<string> messagesQueue;
extern mutex mtx;

int Assignment::execute(string *str, Interpreter *interpreter) {
    string name, value;
    double doubleValue;
    //delete spaces
    size_t findSpace = (*str).find_first_of(" ");
    while (findSpace != string::npos) {
        (*str).replace((*str).find(" "), 1, "");
        findSpace = (*str).find_first_of(" ");
    }
    //split it into Var name , value
    size_t findEqual = str->find_first_of("=");
    if (findEqual != string::npos) {
        name = (*str).substr(0, findEqual);
        value = (*str).substr(findEqual + 1);
    }
    //if the value is an expression
    if (value.find_first_of("+-/*") != string::npos) {
        Expression *ex = interpreter->interpret(value);
        doubleValue = ex->calculate();
    } else {
        //the value is just a number
        doubleValue = stod(value);
    }
    //Update value in fly map
    auto c = flyMap.find(name);
    if (mtx.try_lock()) {
        c->second->setValue(doubleValue);
        mtx.unlock();
    }
    double valueForSet = flyMap.find(name)->second->getValue();
    string valueSetString = to_string(valueForSet);
    //updating the variables map of interpreter
    string strToInterpreter = name + "=" + valueSetString;
    if (mtx.try_lock()) {
        interpreter->setVariables(strToInterpreter);
        mtx.unlock();
    }
    //Prepare set message to simulator
    string path = c->second->getName();
    string messageToSet = "set " + path + " " + valueSetString + "\r\n";
    messagesQueue.push(messageToSet);
    return 2;
}

Assignment::Assignment() {}