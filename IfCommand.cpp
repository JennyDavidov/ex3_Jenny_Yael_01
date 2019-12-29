//
// Created by yael6 on 28/12/2019.
//

#include "IfCommand.h"

#include "Assignment.h"
#include "Sleep.h"
#include "Print.h"
#include "Sim.h"
#include <string>

using namespace std;

int IfCommand::execute(string *str, Interpreter *interpreter) {
    vector<string> commands;
    vector<string>::iterator it;
    it = commands.begin();
    //str += 1;
    int i = 0;
    //keeping condition of while
    (*str).replace((*str).find("{"), 1, "");
    string condition = (*str);
    str += 1;
    //inserting the commands of the while to a vector
    while ((*str) != "}") {
        commands.insert(it, 1, (*str));
        it++;
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
        //finding the condition of the while
        if (reinterpret_cast<const char *>(condition[findEqual]) == "!") {
            cond = "!=";
        } else if (reinterpret_cast<const char *>(condition[findEqual]) == "<") {
            if (reinterpret_cast<const char *>(condition[findEqual + 1]) == "=") {
                cond = "<=";
            } else {
                cond = "<";
            }
        } else if (reinterpret_cast<const char *>(condition[findEqual]) == ">") {
            if (reinterpret_cast<const char *>(condition[findEqual + 1]) == "=") {
                cond = ">=";
            } else {
                cond = ">";
            }
        } else {
            cond = "==";
        }
        //dividing the expression to left and right
        name = (condition).substr(0, findEqual);
        left = interpreter->interpret(name);
        if (cond.length() == 2) {
            value = (condition).substr(findEqual + 2);
        } else {
            value = (condition).substr(findEqual + 1);
        }
        right = interpreter->interpret(value);
        //making the while loop
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
    for (int i = 0; i < commands.size(); i++) {
        if (commands.at(i) == "Print") {
            Print *print = new Print();
            print->execute(&commands.at(i+1), interpreter);
            i++;
        } else if (commands.at(i) == "Sleep") {
            Sleep *sleep = new Sleep();
            sleep->execute(&commands.at(i+1), interpreter);
            i++;
        } else if (commands.at(i) == "var") {
            Sim *var = new Sim();
            var->execute(&commands.at(i+1), interpreter);
            i++;
        } else {
            Assignment *ass = new Assignment();
            ass->execute(&commands.at(i+1), interpreter);
            i++;
        }
    }

}
