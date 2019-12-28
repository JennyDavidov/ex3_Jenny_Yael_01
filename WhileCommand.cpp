//
// Created by yael6 on 28/12/2019.
//

#include "WhileCommand.h"
#include "Assignment.h"
#include "Sleep.h"
#include "Print.h"
#include "Sim.h"
#include <string>

using namespace std;


int WhileCommand::execute(string *str, Interpreter *interpreter) {
    vector<string> commands;
    vector<string>::iterator it;
    it = commands.begin();
    str += 1;
    int i = 0;
    //keeping condition of while
    (*str).replace((*str).find("{"), 1, "");
    string condition = (*str);
    str += 1;
    //inserting the commands of the while to a vector
    while ((*str) != "}") {
        commands.insert(it, i, (*str));
        i++;
        str += 1;
    }
    //delete spaces from condition
    size_t findSpace = (*str).find_first_of(" ");
    while (findSpace != string::npos) {
        (*str).replace((*str).find(" "), 1, "");
        findSpace = (*str).find_first_of(" ");
    }
    size_t findEqual = str->find_first_of("!<>=");
    string name, value, cond;
    Expression *left, *right;
    if (findEqual != string::npos) {
        //finding the condition of the while
        if (str[findEqual] == "!") {
            cond = "!=";
        } else if (str[findEqual] == "<") {
            if (str[findEqual + 1] == "=") {
                cond = "<=";
            } else {
                cond = "<";
            }
        } else if (str[findEqual] == ">") {
            if (str[findEqual + 1] == "=") {
                cond = ">=";
            } else {
                cond = ">";
            }
        } else {
            cond = "==";
        }
        //dividing the expression to left and right
        name = (*str).substr(0, findEqual);
        left = interpreter->interpret(name);
        if (cond.length() == 2) {
            value = (*str).substr(findEqual + 2);
        } else {
            value = (*str).substr(findEqual + 1);
        }
        right = interpreter->interpret(value);
        //making the while loop
        if (cond == "!=") {
            while (left->calculate() != right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == "<=") {
            while (left->calculate() <= right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == "<") {
            while (left->calculate() < right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == ">=") {
            while (left->calculate() >= right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == ">") {
            while (left->calculate() > right->calculate()) {
                callingCommand(commands, interpreter);
            }
        } else if (cond == "==") {
            while (left->calculate() == right->calculate()) {
                callingCommand(commands, interpreter);
            }
        }

    }
    return (i + 3);
}

WhileCommand::WhileCommand() {}

void WhileCommand::callingCommand(vector<string> commands, Interpreter *interpreter) {
    for (int i = 0; i < commands.size(); i++) {
        size_t isPrint = commands.at(i).find("Print");
        if (isPrint != string::npos) {
            Print *print = new Print();
            size_t index = commands.at(i).find_first_of("(");
            string value = commands.at(i).substr(index + 1, commands.at(i).length() - 1);
            print->execute(&value, interpreter);
            continue;
        }
        size_t isSleep = commands.at(i).find("Sleep");
        if (isSleep != string::npos) {
            Sleep *sleep = new Sleep();
            size_t index = commands.at(i).find_first_of("(");
            string value = commands.at(i).substr(index + 1, commands.at(i).length() - 1);
            sleep->execute(&value, interpreter);
            continue;
        }
        size_t isVar = commands.at(i).find("var");
        if (isVar != string::npos) {
            Sim *var = new Sim();
            string value = commands.at(i).substr(4);
            var->execute(&value, interpreter);
            continue;
        }
        Assignment *ass = new Assignment();
        ass->execute(&commands.at(i), interpreter);
    }

}
