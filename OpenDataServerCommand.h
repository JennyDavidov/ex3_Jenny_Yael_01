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
    static void openServer(string *str, int client_socket);
    OpenDataServerCommand();

    int execute(string *str, Interpreter* interpreter);
    void simulatorMapCreate(int client_socket);
};

#endif //EX3_TEST_PROJ_OPENDATASERVERCOMMAND_H
