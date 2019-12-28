//
// Created by yael6 on 28/12/2019.
//

#ifndef EX3_TEST_PROJ_WHILECOMMAND_H
#define EX3_TEST_PROJ_WHILECOMMAND_H
#include "Command.h"
#include <string>
using namespace std;

class WhileCommand : public Command{
public:
    WhileCommand();

    int execute(string *str, Interpreter* interpreter);
    void callingCommand(vector<string> commands, Interpreter* interpreter);

};


#endif //EX3_TEST_PROJ_WHILECOMMAND_H
