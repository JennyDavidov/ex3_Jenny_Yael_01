//
// Created by jenny on 19/12/2019.
//

#ifndef EX3_TEST_PROJ_CONNECTCONTROLCLIENTCOMMAND_H
#define EX3_TEST_PROJ_CONNECTCONTROLCLIENTCOMMAND_H

#include "Command.h"
#include <string>
using namespace std;

class ConnectControlClientCommand : public Command {
public:
    ConnectControlClientCommand();

    int execute(string *str);

};
#endif //EX3_TEST_PROJ_CONNECTCONTROLCLIENTCOMMAND_H
