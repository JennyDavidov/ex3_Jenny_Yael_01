//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_SIM_H
#define EX3_TEST_PROJ_SIM_H

#include "Command.h"
#include <string>
using namespace std;

class Sim : public Command {
public:
    Sim();

    int execute(string &str);
};

#endif //EX3_TEST_PROJ_SIM_H
