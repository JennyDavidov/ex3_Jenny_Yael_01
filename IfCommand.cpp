//
// Created by yael6 on 28/12/2019.
//

#include "IfCommand.h"
#include "Assignment.h"
#include "Sleep.h"
#include "Print.h"
#include "Sim.h"
#include <string>

extern map<string, Variable *> flyMap;
using namespace std;

int IfCommand::execute(string *str, Interpreter *interpreter) {
    vector<string> commands;
    vector<string>::iterator it;
    int i = 0;
    //keeping condition of if
    (*str).replace((*str).find("{"), 1, "");
    string condition = (*str);
    str += 1;
    //inserting the commands of the if to a vector
    while ((*str) != "}") {
        commands.insert(commands.begin(), 1, (*str));
        i++;
        str += 1;
    }
    //delete spaces from condition
    size_t findSpace = (condition).find_first_of(" ");
    while (findSpace != string::npos) {
        (condition).replace((condition).find(" "), 1, "");
        findSpace = (condition).find_first_of(" ");
    }
    size_t findEqual = condition.find_first_of("!<>=");
    string name, value, cond;
    Expression *left, *right;
    if (findEqual != string::npos) {
        //finding the condition of the if
        if ((condition[findEqual]) == '!') {
            cond = "!=";
        } else if ((condition[findEqual]) == '<') {
            if ((condition[findEqual + 1]) == '=') {
                cond = "<=";
            } else {
                cond = "<";
            }
        } else if ((condition[findEqual]) == '>') {
            if ((condition[findEqual + 1]) == '=') {
                cond = ">=";
            } else {
                cond = ">";
            }
        } else {
            cond = "==";
        }
        //dividing the expression to left expression and right expression
        name = (condition).substr(0, findEqual);
        if (name.find_first_of("+-/*") != string::npos) {
            left = interpreter->interpret(name);
        } else {
            left = new Value(flyMap.find(name)->second->getValue());
        }
        if (cond.length() == 2) {
            value = (condition).substr(findEqual + 2);
        } else {
            value = (condition).substr(findEqual + 1);
        }
        if (value.find_first_of("+-/*") != string::npos) {
            right = interpreter->interpret(value);
        } else {
            right = new Value(stod(value));
        }
        //making the if scope and calling commands if the condition is correct
        if (cond == "!=") {
            if (left->calculate() != right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == "<=") {
            if (left->calculate() <= right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == "<") {
            if (left->calculate() < right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == ">=") {
            if (left->calculate() >= right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == ">") {
            if (left->calculate() > right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == "==") {
            if (left->calculate() == right->calculate()) {
                callingCommand(commands, interpreter);
            }
        }
    }
    return (i + 3);
}

IfCommand::IfCommand() {}

void IfCommand::callingCommand(vector<string> commands, Interpreter *interpreter) {
    //going through commands of the "if" scope and call their execute
    for (int i = commands.size()-1; i >= 0; i--) {
        if (commands.at(i) == "Print") {
            Print *print = new Print();
            print->execute(&commands.at(i-1), interpreter);
            i--;
        } else if (commands.at(i) == "Sleep") {
            Sleep *sleep = new Sleep();
            sleep->execute(&commands.at(i-1), interpreter);
            i--;
        } else if (commands.at(i) == "var") {
            Sim *var = new Sim();
            var->execute(&commands.at(i-1), interpreter);
            i--;
        } else {
            Assignment *ass = new Assignment();
            ass->execute(&commands.at(i-1), interpreter);
            i--;
        }
    }
}
