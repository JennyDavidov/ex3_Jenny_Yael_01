//
// Created by jenny on 19/12/2019.
//

#include "Print.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;

int Print::execute(string *str, Interpreter *interpreter) {
    string s = *str;
    //if the value to print is a string
    if (s.find("\"") != string::npos) {
        //erasing the ""
        s.erase(0, 1);
        s.erase(s.length() - 1, 1);
        cout << s << endl;
    }
    //if the value to print is an expression
    else {
        //if it's a binary expression
        if ((*str).find_first_of("+-/*") != string::npos) {
            Expression *ex = interpreter->interpret(*str);
            double temp = ex->calculate();
            //converting the double to string
            s = to_string(temp);
            cout << s << endl;
        }
        //if it's a unary expression, a name of variable to print it's value
        else {
            //finding the variable on flyMap
            auto c = flyMap.find(s);
            double d = c->second->getValue();
            //converting the double to string
            s = to_string(d);
            cout << s << endl;
        }
        chrono::duration<int, milli> dur(1000);
        this_thread::sleep_for(dur);
    }
    return 2;
}

Print::Print() {}