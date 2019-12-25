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
#include "xml.h"
#include "Expression.h"
#include "interpreter.h"

using namespace std;

vector<string> lexerFunc(ifstream &file);

void parserFunc(vector<string> array, map<string, Command *>, Interpreter* interpreter);

map<string, Command *> mapCreator();

int main(int argc, char *argv[]) {

    map<string, Command *> commandMap;
    vector<string> array;
    //vector<string> xmlDetails;
    Interpreter* interpreter = new Interpreter();
    //no arguments provided
    if (argc == 0) {
        cerr << "Exception, no arguments provided" << endl;
        return -1;
    } else {
        const char *filename = argv[1];
        ifstream in_file(filename);
        //checking in_file opened fine
        if (!in_file) {
            cerr << "Error opening in_file" << endl;
            return -1;
        } else {
            //xmlDetails = readingXml();
            array = lexerFunc(in_file);
            commandMap = mapCreator();
            parserFunc(array, commandMap, interpreter);
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

map<string, Command *> mapCreator() {
    map<string, Command *> commandMap;
    Command *open = new OpenDataServerCommand();
    Command *connect = new ConnectControlClientCommand;
    Command *sim = new Sim;
    Command *sleep = new Sleep;
    Command *print = new Print;
    commandMap["openDataServer"] = open;
    commandMap.emplace("connectControlClient", connect);
    commandMap.emplace("sim", sim);
    commandMap.emplace("sleep", sleep);
    commandMap.emplace("print", print);

    return commandMap;
}

void parserFunc(vector<string> array, map<string, Command *> mapCommand, Interpreter* interpreter) {
    int index = 0;
    while (index < array.size()) {
        if (mapCommand.find(array[index]) != mapCommand.end()) {
            auto c = mapCommand.find(array[index])->second;
            OpenDataServerCommand *open = dynamic_cast<OpenDataServerCommand *>(c);
            if (open) {
                index += open->execute(&array.at(index), interpreter);
            }
//            ConnectControlClientCommand *connect = dynamic_cast<ConnectControlClientCommand *>(c);
//            if (connect) {
//                index += connect->execute(array.at(index));
//            }
//            Sleep *sleep = dynamic_cast<Sleep *>(c);
//            if (sleep) {
//                index += sleep->execute(array.at(index));
//            }
//            Print *print = dynamic_cast<Print *>(c);
//            if (print) {
//                index += print->execute(array.at(index));
//            }
//            Sim *sim = dynamic_cast<Sim *>(c);
//            if (sim) {
//                index += sim->execute(array.at(index));
//            }
        }
    }
}

