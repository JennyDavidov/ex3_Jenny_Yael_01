//
// Created by jenny on 25/12/2019.
//

#ifndef EX3_TEST_PROJ_ASSIGNMENT_H
#define EX3_TEST_PROJ_ASSIGNMENT_H
#include "Command.h"
#include <string>
using namespace std;

class Assignment : public Command {
public:
    Assignment();

    int execute(string *str, Interpreter *interpreter);

};



#endif //EX3_TEST_PROJ_ASSIGNMENT_H
