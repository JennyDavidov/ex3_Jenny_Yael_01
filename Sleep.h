//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_SLEEP_H
#define EX3_TEST_PROJ_SLEEP_H
#include "Command.h"
#include <string>
using namespace std;

class Sleep : public Command {
public:
    Sleep();

    int execute(string *str);

};

#endif //EX3_TEST_PROJ_SLEEP_H
