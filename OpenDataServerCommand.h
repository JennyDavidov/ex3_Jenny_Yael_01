//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_OPENDATASERVERCOMMAND_H
#define EX3_TEST_PROJ_OPENDATASERVERCOMMAND_H

#include "Command.h"
#include <string>

using namespace std;

class OpenDataServerCommand : public Command {
public:
    OpenDataServerCommand();

    int execute(string *str);

};

#endif //EX3_TEST_PROJ_OPENDATASERVERCOMMAND_H
