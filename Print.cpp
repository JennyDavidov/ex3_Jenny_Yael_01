//
// Created by jenny on 19/12/2019.
//

#include "Print.h"
#include "ConnectControlClientCommand.h"
#include <string>
#include <iostream>

using namespace std;


int Print::execute(string *str, Interpreter *interpreter) {
    str += 1;
    string s = *str;
    s.erase(0, 1);
    s.erase(s.length() - 1, 1);
    cout << s << endl;
    return 2;
}

Print::Print() {}