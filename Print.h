//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_PRINT_H
#define EX3_TEST_PROJ_PRINT_H

#include "Command.h"
#include <string>
using namespace std;

class Print : public Command {
public:
    Print();

    int execute(string *str);

};

#endif //EX3_TEST_PROJ_PRINT_H
