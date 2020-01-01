//
// Created by jenny on 19/12/2019.
//

#include "Print.h"
#include "ConnectControlClientCommand.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;

int Print::execute(string *str, Interpreter *interpreter) {
   // str += 1;
    string s = *str;
    if (s.find("\"") != string::npos) {
        s.erase(0, 1);
        s.erase(s.length() - 1, 1);
        cout << s << endl;
    }
    else {
        auto c = flyMap.find(s);
        double d = c->second->getValue();
        s = to_string(d);
        cout << s << endl;
        chrono::duration<int, milli> dur(1000);
        this_thread::sleep_for(dur);
    }
    return 2;
}

Print::Print() {}