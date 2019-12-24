//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_COMMAND_H
#define EX3_TEST_PROJ_COMMAND_H

#include <string>
#include "ex1.h"

using namespace std;
static map<string, Variable *> simulatorMap;
static map<string, Variable *> flyMap;

class Command {
public:

    virtual int execute(string &str) {};

    virtual ~Command() {};
};

#endif //EX3_TEST_PROJ_COMMAND_H
