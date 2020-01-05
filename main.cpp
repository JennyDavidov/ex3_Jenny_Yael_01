#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include "Command.h"
#include "OpenDataServerCommand.h"
#include "ConnectControlClientCommand.h"
#include "Sim.h"
#include "Sleep.h"
#include "Print.h"
#include "xml.h"
#include "interpreter.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "Assignment.h"
#include <mutex>
#include <queue>

using namespace std;
extern string xmlDetails[36];
map<string, Variable *> simulatorMap;
map<string, Variable *> flyMap;
queue<string> messagesQueue;

vector<string> lexerFunc(ifstream &file);

void parserFunc(vector<string> array, map<string, Command *>, Interpreter *interpreter);

map<string, Command *> mapCreator();

int main(int argc, char *argv[]) {

    map<string, Command *> commandMap;
    vector<string> array;
    Interpreter *interpreter = new Interpreter();
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
            readingXml();
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
    //reading the first line
    getline(file, buffer);
    //deleting spaces from beginning of line
    while(buffer[i] == ' ') {
        buffer.replace(i, 1, "");
        i++;
    }
    //separate it by ( or ,
    size_t index = buffer.find_first_of("(,");
    while (index != string::npos) {
        param = buffer.substr(i, index);
        if (param.find("\t") != string::npos) {
            param.replace(param.find("\t"), 1, "");
        }
        buffer = buffer.substr(index + 1);
        array.push_back(param);
        index = buffer.find_first_of("(,");
    }
    param = buffer.erase(buffer.length() - 1);
    if (param.find("\t") != string::npos) {
        param.replace(param.find("\t"), 1, "");
    }
    array.push_back(param);
    //reading all other lines of file
    while (getline(file, buffer)) {
        //deleting spaces from beginning of line
        while(buffer[i] == ' ') {
            buffer.replace(i, 1, "");
            i++;
        }
        //if the line is var definition
        size_t isVar = buffer.find("var");
        if (isVar != string::npos) {
            array.push_back("var");
            buffer = buffer.substr(i+4);
            index = buffer.find("->");
            if (index == string::npos) {
                index = buffer.find("<-");
            }
            if (index == string::npos) {
                if (buffer.find("\t") != string::npos) {
                    buffer.replace(buffer.find("\t"), 1, "");
                }
                array.push_back(buffer);
            } else {
                //insert name variable
                param = buffer.substr(0, index);
                param.replace(param.find(" "), 1, "");
                array.push_back(param);
                buffer = buffer.substr(index);
                //insert arrow
                param = buffer.substr(0, 2);
                array.push_back(param);
                buffer = buffer.substr(2);
                //insert the word 'sim'
                index = buffer.find_first_of("(");
                param = buffer.substr(0, index);
                param.replace(param.find(" "), 1, "");
                array.push_back(param);
                //insert sim directory
                buffer = buffer.substr(index + 1);
                buffer.erase(buffer.length() - 1);
                buffer.erase(0, 1);
                buffer.erase(buffer.length() - 1, 1);
                array.push_back(buffer);
            }
        }
        //other lines that aren't var definition
        else {
            if (buffer.find("while") != string::npos) {
                //inserting 'while'
                param = buffer.substr(i, 5);
                array.push_back(param);
                //insert rest of buffer
                buffer = buffer.substr(i+6);
                array.push_back(buffer);
            } else if (buffer.find("if") != string::npos) {
                //insert 'if'
                param = buffer.substr(i, 2);
                array.push_back(param);
                //insert rest of buffer
                buffer = buffer.substr(i+3);
                array.push_back(buffer);
            } else if (buffer.find("=") != string::npos) {
                if (buffer.find("\t") != string::npos) {
                    buffer.replace(buffer.find("\t"), 1, "");
                }
                array.push_back("ass");
                array.push_back(buffer);
            } else if (buffer.find('}') != string::npos) {
                array.push_back(buffer);
            } else {
                //reading other lines that didn't match earlier conditions
                index = buffer.find_first_of("(,");
                while (index != string::npos) {
                    param = buffer.substr(i, index);
                    if (param.find("\t") != string::npos) {
                        param.replace(param.find("\t"), 1, "");
                    }
                    buffer = buffer.substr(index + 1);
                    array.push_back(param);
                    index = buffer.find_first_of("(,");
                }
                buffer.erase(buffer.length() - 1);
                array.push_back(buffer);
            }
        }
    }
    return array;
}

map<string, Command *> mapCreator() {
    map<string, Command *> commandMap;
    //making new objects of commands
    Command *open = new OpenDataServerCommand();
    Command *connect = new ConnectControlClientCommand();
    Command *sim = new Sim();
    Command *sleep = new Sleep();
    Command *print = new Print();
    Command *ass = new Assignment();
    Command *whileCommand = new WhileCommand();
    Command *ifCommand = new IfCommand();
    //insert to map the key and the command object
    commandMap.emplace("openDataServer", open);
    commandMap.emplace("connectControlClient", connect);
    commandMap.emplace("var", sim);
    commandMap.emplace("Sleep", sleep);
    commandMap.emplace("Print", print);
    commandMap.emplace("ass", ass);
    commandMap.emplace("while", whileCommand);
    commandMap.emplace("if", ifCommand);
    return commandMap;
}

void parserFunc(vector<string> array, map<string, Command *> mapCommand, Interpreter *interpreter) {
    unsigned int index = 0;
    //going through the array we made from the lexer and dynamic cast each command and call their execute
    while (index < array.size()) {
        if (mapCommand.find(array[index]) != mapCommand.end()) {
            auto c = mapCommand.find(array[index])->second;
            OpenDataServerCommand *open = dynamic_cast<OpenDataServerCommand *>(c);
            if (open) {
                index += open->execute(&array.at(index+1), interpreter);
            }
            ConnectControlClientCommand *connect = dynamic_cast<ConnectControlClientCommand *>(c);
            if (connect) {
                index += connect->execute(&array.at(index+1), interpreter);
            }
            Sleep *sleep = dynamic_cast<Sleep *>(c);
            if (sleep) {
                index += sleep->execute(&array.at(index+1), interpreter);
            }
            Print *print = dynamic_cast<Print *>(c);
            if (print) {
                index += print->execute(&array.at(index+1), interpreter);
            }
            Sim *sim = dynamic_cast<Sim *>(c);
            if (sim) {
                index += sim->execute(&array.at(index+1), interpreter);
            }
            Assignment *ass = dynamic_cast<Assignment *>(c);
            if (ass) {
                index += ass->execute(&array.at(index+1), interpreter);
            }
            WhileCommand *whileCommand = dynamic_cast<WhileCommand *>(c);
            if (whileCommand) {
                index += whileCommand->execute(&array.at(index+1), interpreter);
            }
            IfCommand *ifCommand = dynamic_cast<IfCommand *>(c);
            if (ifCommand) {
                index += ifCommand->execute(&array.at(index+1), interpreter);
            }

        }
    }
    parserDone = true;
}

