//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_COMMAND_H
#define EX3_TEST_PROJ_COMMAND_H

#include <string>
#include "interpreter.h"
#include "ex1.h"

using namespace std;

static map<string, Variable *> simulatorMap;
static map<string, Variable *> flyMap;
static bool parserDone = false;
static const char *message = NULL;

class Command {
public:

public:
    virtual int execute(string &str, Interpreter *interpreter) {};

    virtual ~Command() {};
};

#endif //EX3_TEST_PROJ_COMMAND_H
