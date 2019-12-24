//
// Created by jenny on 19/12/2019.
//

#include "Print.h"
#include "ConnectControlClientCommand.h"
#include <string>
#include <iostream>

using namespace std;


int Print::execute(string &str) {
    str += 1;
    string s = str;
    cout << str;
}

Print::Print() {}