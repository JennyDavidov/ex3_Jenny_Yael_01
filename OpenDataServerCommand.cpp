//
// Created by jenny on 19/12/2019.
//
#include <string>
#include "OpenDataServerCommand.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <map>
#include "ex1.h"
#include "Expression.h"
#include "interpreter.h"
#include <mutex>


using namespace std;
extern string xmlDetails[36];
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;
extern mutex mtx;

int OpenDataServerCommand::execute(string *str, Interpreter *interpreter) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        exit(-1);
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    unsigned short port;
    //if port is an expression
    if (str->find_first_of("+-/*") != string::npos) {
        Expression *ex = interpreter->interpret(*str);
        port = ex->calculate();
    } else {
        //if port is a number
        port = stod(*str);
    }
    address.sin_port = htons(port);
    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        exit(-1);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        exit(-1);
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);
    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        exit(-1);
    }
    //closing the listening socket
    close(socketfd);
    //creating simulator map for the first time
    simulatorMapCreate(client_socket);
    //create thread
    thread serverThread(openServer, str, client_socket, interpreter);
    serverThread.detach();
    return 2;
}

OpenDataServerCommand::OpenDataServerCommand() {}

void OpenDataServerCommand::openServer(string *str, int client_socket, Interpreter *interpreter) {
    int j = 0;
    char buffer[1024] = "";
    string readData = "";
    string temp = "";
    bool firstValues;
    string sBegin = "", sEnd = "";
    chrono::duration<int, milli> d(1500);
    //while we have things to read from simulator
    while (read(client_socket, buffer, 1024) > 0) {
        this_thread::sleep_for(d);
        firstValues = true;
        j = 0;
        //convert char array to string
        string s = "";
        string check;
        for (unsigned int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\0') {
                break;
            }
            s = s + buffer[i];
        }
        //while we didn't finish passing the s string
        while (s.length() > 0) {
            size_t index = s.find_first_of("\n");
            while (index != string::npos) {
                //no previous buffer
                if (sEnd.length() == 0) {
                    if (firstValues) {
                        //throwing values until /n
                        s = s.substr(index + 1);
                        firstValues = false;
                    }
                    size_t index1 = s.find_first_of("\n");
                    //string from /n to /n
                    readData = (s).substr(0, index1);
                    s = s.substr(index1 + 1);
                } else {
                    if (firstValues) {
                        firstValues = false;
                    }
                    sBegin = s.substr(0, index);
                    //merging end from previous buffer and begin of this buffer
                    readData = sEnd + sBegin;
                    sEnd = "";
                    s = s.substr(index + 1);

                }
                //deleting commas from the beginning and end of string
                if (readData[0] == ',') {
                    readData.erase(0, 1);
                }
                if (readData[readData.length() - 1] == ',') {
                    readData.erase(readData.length() - 1, 1);
                }
                size_t findComma = (readData).find_first_of(",");
                //reading the 36 values and separating them by the comma
                while ((findComma != string::npos) && (j < 36)) {
                    temp = (readData).substr(0, findComma);
                    readData = readData.substr(findComma + 1);
                    double value = stod(temp);
                    //inserting new object
                    if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                        simulatorMap.insert(
                                pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], value)));
                    } else {
                        //updating value of variable object
                        auto c = simulatorMap.find(xmlDetails[j])->second;
                        if (mtx.try_lock()) {
                            c->setValue(value);
                            mtx.unlock();
                        }
                        map<string, Variable *>::iterator it;
                        string key = "";
                        for (it = flyMap.begin(); it != flyMap.end(); ++it) {
                            if (it->second == c) {
                                key = it->first;
                                break;
                            }
                        }
                        //updating the value in the variables map of interpreter
                        if (key != "") {
                            string valueString = to_string(c->getValue());
                            string strToInterpreter = key + "=" + valueString;
                            if (mtx.try_lock()) {
                                interpreter->setVariables(strToInterpreter);
                                mtx.unlock();
                            }
                        }
                    }
                    findComma = (readData).find_first_of(",");
                    j++;
                    //last element received from the simulator
                    if ((j == 35) && (findComma == string::npos) && (readData != "")) {
                        double lastValue = stod(readData);
                        readData = "";
                        //inserting the new value
                        if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                            simulatorMap.insert(
                                    pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], lastValue)));
                        } else {
                            //updating existing value
                            auto c = simulatorMap.find(xmlDetails[j])->second;
                            if (mtx.try_lock()) {
                                c->setValue(lastValue);
                                mtx.unlock();
                            }
                            map<string, Variable *>::iterator it;
                            string key = "";
                            for (it = flyMap.begin(); it != flyMap.end(); ++it) {
                                if (it->second == c) {
                                    key = it->first;
                                    break;
                                }
                            }
                            //updating the value in the variables map of interpreter
                            if (key != "") {
                                string valueString = to_string(c->getValue());
                                string strToInterpreter = key + "=" + valueString;
                                if (mtx.try_lock()) {
                                    interpreter->setVariables(strToInterpreter);
                                    mtx.unlock();
                                }
                            }
                        }
                        j++;
                    }
                }
                index = s.find_first_of("\n");
                j = 0;
            }
            //what remains in s
            sEnd = s;
            s = "";
        }
    }
    close(client_socket);
    return;
}

void OpenDataServerCommand::simulatorMapCreate(int client_socket) {
//reading from client
    int j = 0;
    char buffer[1024] = "";
    string readData = "";
    string temp = "";
    if (read(client_socket, buffer, 1024) > 0) {
        //convert char array to string
        string s = "";
        for (unsigned int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\0') {
                break;
            }
            s = s + buffer[i];
        }
        size_t index = s.find_first_of("\n");
        readData = (s).substr(0, index);
        size_t findComma = (readData).find_first_of(",");
        //reading the 36 values and separating them by the comma
        while ((findComma != string::npos) && (j < 36)) {
            temp = (readData).substr(0, findComma);
            readData = readData.substr(findComma + 1);
            double value = stod(temp);
            //inserting the new variable object
            if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                simulatorMap.insert(pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], value)));
            }
            findComma = (readData).find_first_of(",");
            j++;
            //inserting the last variable object
            if ((j == 35) && (findComma == string::npos) && (readData != "")) {
                double lastValue = stod(readData);
                readData = "";
                if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                    simulatorMap.insert(pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], lastValue)));
                }
                j++;
            }
        }
    }
    return;
}
