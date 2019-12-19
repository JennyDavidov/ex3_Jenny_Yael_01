#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <iterator>
#include <map>
#include "Command.h"
#include "OpenDataServerCommand.h"
#include "ConnectControlClientCommand.h"
#include "Sim.h"
#include "Sleep.h"
#include "Print.h"


using namespace std;

vector<string> lexerFunc(ifstream &file);

void parserFunc(vector<string> array, map<string, Command>);

map<string, Command> mapCreator();

int main(int argc, char *argv[]) {

    map<string, Command> commandMap;
    vector<string> array;
    //no arguments provided
    if (argc == 0) {
        cout << "Exception, no arguments provided" << endl;
        return -1;
    } else {
        const char *filename = argv[1];
        ifstream in_file(filename);
        //checking in_file opened fine
        if (!in_file) {
            cout << "Error opening in_file" << endl;
            return -1;
        } else {
            array = lexerFunc(in_file);
            commandMap = mapCreator();
            parserFunc(array,commandMap);
        }
        in_file.close();
    }
    return 0;
}

vector<string> lexerFunc(ifstream &file) {
    vector<string> array;
    int i = 0;
    string buffer, param;
    getline(file, buffer);
    size_t index = buffer.find_first_of("(,");
    while (index != string::npos) {
        param = buffer.substr(0, index);
        if (param.find("\t") != string::npos) {
            int i = param.find("\t");
            param.replace(param.find("\t"), 1, "");
        }
        buffer = buffer.substr(index + 1);
        array.push_back(param);
        index = buffer.find_first_of("(,");
    }
    param = buffer.erase(buffer.length() - 1);
    if (param.find("\t") != string::npos) {
        int i = param.find("\t");
        param.replace(param.find("\t"), 1, "");
    }
    array.push_back(param);
    while (getline(file, buffer)) {
        //if the line is var definition
        size_t isVar = buffer.find("var");
        if (isVar != string::npos) {
            array.push_back("var");
            buffer = buffer.substr(4);
            index = buffer.find_first_of(" (");
            while (index != string::npos) {
                param = buffer.substr(0, index);
                if (param.find("\t") != string::npos) {
                    int i = param.find("\t");
                    param.replace(param.find("\t"), 1, "");
                }
                buffer = buffer.substr(index + 1);
                array.push_back(param);
                index = buffer.find_first_of(" (");
            }
            param = buffer.erase(buffer.length() - 1);
            array.push_back(param);
        }
            //other lines that aren't var definition
        else {
            if ((buffer.find("while") != string::npos) || (buffer.find("if") != string::npos) ||
                (buffer.find(" = ") != string::npos)
                || (buffer.find('}') != string::npos)) {
                array.push_back(buffer);
            } else {
                index = buffer.find_first_of("(,");
                while (index != string::npos) {
                    param = buffer.substr(0, index);
                    if (param.find("\t") != string::npos) {
                        int i = param.find("\t");
                        param.replace(param.find("\t"), 1, "");
                    }
                    buffer = buffer.substr(index + 1);
                    array.push_back(param);
                    index = buffer.find_first_of("(,");
                }
                param = buffer.erase(buffer.length() - 1);
                array.push_back(param);
            }
        }
    }
    return array;
}

map<string, Command> mapCreator() {
    map<string, Command> commandMap;
    OpenDataServerCommand open;
    ConnectControlClientCommand connect;
    Sim sim;
    Sleep sleep;
    Print print;
    commandMap.emplace("openDataServer", open);
    commandMap.emplace("connectControlClient", connect);
    commandMap.emplace("connectControlClient", connect);
    commandMap.emplace("sim", sim);
    commandMap.emplace("sleep", sleep);
    commandMap.emplace("print", print);

    return commandMap;
}

void parserFunc(vector<string> array, map<string, Command> mapCommand) {
    int index = 0;
    //Command c;
    while (index < array.size()) {
        if (mapCommand.find(array[index]) != mapCommand.end()) {
            auto c = (mapCommand.find(array[index]))->second;
            index += c.execute(&array[index]);
        }
    }
}

