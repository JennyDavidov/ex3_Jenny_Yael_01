//
// Created by yael6 on 13/11/2019.
//

#ifndef EX1_INTERPRETER_H
#define EX1_INTERPRETER_H

#include "ex1.h"
#include "Expression.h"
#include <string>
#include <map>
#include <stack>
#include <queue>
using namespace std;

class Interpreter {
    map<string,string> variables;
public:
    Interpreter();
    virtual ~Interpreter();
    void setVariables(string str);
    Expression* interpret(string string);
    bool isEqualOp(stack<string> s, char op);
    bool isHighOp(stack<string> s, char op);
    Expression* anotherExp(queue<string> &output, stack<double> &nums, Expression* ex1);
};



#endif //EX1_INTERPRETER_H
