//
// Created by jenny on 19/12/2019.
//

#include "Print.h"
#include "ConnectControlClientCommand.h"
#include <string>
#include <iostream>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;

int Print::execute(string *str, Interpreter *interpreter) {
   // str += 1;
    string s = *str;
    if (s.find("\"") != string::npos) {
        s.erase(0, 1);
        s.erase(s.length() - 1, 1);
    }
    else {
        auto c = flyMap.find(s);
        double d = c->second->getValue();
        s = to_string(d);
    }
    cout << s << endl;
    return 2;
}

Print::Print() {}