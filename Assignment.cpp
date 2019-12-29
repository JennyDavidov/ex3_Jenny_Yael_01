//
// Created by jenny on 25/12/2019.
//

#include "Assignment.h"
#include "Sleep.h"
#include <string>
#include <cstring>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;
extern string message;
string globalName;
double globalValue;

int Assignment::execute(string *str, Interpreter *interpreter) {
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
        doubleValue = stod(value);
    }
    //updating global values
    globalName = name;
    globalValue = doubleValue;
    //Update value in fly map
    auto c = flyMap.find(name);
//    c->second->setValue(doubleValue);
    //Prepare set message to simulator
    string path = c->second->getName();
    //double valueForSet = flyMap.find(name)->second->getValue();
    string valueSetString = to_string(doubleValue);
    string strToInterpreter = name + "=" + valueSetString;
    interpreter->setVariables(strToInterpreter);
    string messageToSet = "set " + path + " " + valueSetString + "\r\n";
    message = messageToSet;
    return 2;
}

Assignment::Assignment() {}