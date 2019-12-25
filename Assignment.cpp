//
// Created by jenny on 25/12/2019.
//

#include "Assignment.h"
#include "Sleep.h"
#include <string>

using namespace std;


int Assignment::execute(string *str, Interpreter *interpreter) {
    //skip the "ass"
    str+=1;
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

}

Assignment::Assignment() {}