//
// Created by jenny on 19/12/2019.
//

#include "Sleep.h"
#include <string>
#include <thread>

using namespace std;


int Sleep::execute(string *str, Interpreter *interpreter) {
    double temp;
    int duration;
    //if the value of sleep command is a binary expression
    if ((*str).find_first_of("+-/*") != string::npos) {
        Expression *ex = interpreter->interpret(*str);
        temp = ex->calculate();
        duration = (int) temp;
    }
    //if the value of sleep command is a unary expression
    else {
        string::size_type sz;
        duration = stoi(*str,&sz);
    }
    //sleeping the thread according the value we got
    chrono::duration<int, milli> d(duration);
    this_thread::sleep_for(d);
    return 2;
}

Sleep::Sleep() {}

