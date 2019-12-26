//
// Created by jenny on 25/12/2019.
//

#include "Assignment.h"
#include "Sleep.h"
#include <string>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;

int Assignment::execute(string *str, Interpreter *interpreter) {
    //skip the "ass"
    str += 1;
    //if the string contains expression
    //split it into Var name , value
    string name, value;
    double doubleValue;
    //delete spaces
    size_t findSpace = (*str).find_first_of(" ");
    while (findSpace != string::npos) {
        (*str).replace((*str).find(" "), 1, "");
        findSpace = (*str).find_first_of(" ");
    }
    size_t findEqual = str->find_first_of("=");
    if (findEqual != string::npos) {
        name = (*str).substr(0, findEqual);
        value = (*str).substr(findEqual + 1);
    }
    if (value.find_first_of("+-/*") != string::npos) {
        Expression *ex = interpreter->interpret(*str);
        doubleValue = ex->calculate();
    } else {
        doubleValue = stod(*str);
    }
    //Update value in fly map
    flyMap.find(name)->second->setValue(doubleValue);
    //Prepare set message to simulator
    string path = flyMap.find(name)->second->getName();
    path = path.erase(0, 1);
    path = path.erase(path.length() - 1);
    double valueForSet = flyMap.find(name)->second->getValue();
    string valueSetString = to_string(valueForSet);
    string messageToSet = "set " + path + " " + valueSetString + "\r\n";
    message = messageToSet.c_str();
}

Assignment::Assignment() {}