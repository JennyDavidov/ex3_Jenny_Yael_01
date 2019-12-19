//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_COMMAND_H
#define EX3_TEST_PROJ_COMMAND_H

#include <string>
using namespace std;



class Command {
public:
    virtual int execute(string* str) = 0;
    virtual ~Command();
};
#endif //EX3_TEST_PROJ_COMMAND_H
