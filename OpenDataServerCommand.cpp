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
#include <string>
#include <cstring>
#include <map>
#include "ex1.h"
#include "xml.h"
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
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    // str += 1;
    unsigned short port;
    if (str->find_first_of("+-/*") != string::npos) {
        Expression *ex = interpreter->interpret(*str);
        port = ex->calculate();
    } else {
        port = stod(*str);
    }
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        exit(-1);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
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
    close(socketfd); //closing the listening socket
    simulatorMapCreate(client_socket);
    thread serverThread(openServer, str, client_socket);
    serverThread.detach();
    return 2;
}

OpenDataServerCommand::OpenDataServerCommand() {}

void OpenDataServerCommand::openServer(string *str, int client_socket) {

    //reading from client
    int j = 0;
    int n = 0;
    char buffer[1024] = "";
    string readData = "";
    string temp = "";
    bool firstValues;
    string sBegin = "", sEnd = "";
    while (read(client_socket, buffer, 1024) > 0) {
        firstValues = true;
        j = 0;
        //convert char array to string
        string s = "";
        string check;
        for (int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\0') {
                break;
            }
            s = s + buffer[i];
        }
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
//                check = readData;
//                int i = 0;
//                size_t findComma1 = check.find_first_of(",");
//                while (findComma1 != string::npos) {
//                    check.replace(check.find(","), 1, "");
//                    findComma1 = check.find_first_of(",");
//                    i++;
//                }
//                if (i != 35) {
//                    continue;
//                    index = s.find_first_of("\n");
//                }
                if (readData[0] == ',') {
                    readData.erase(0,1);
                }
                if (readData[readData.length() - 1] == ',') {
                    readData.erase(readData.length()-1, 1);
                }
                size_t findComma = (readData).find_first_of(",");
                while ((findComma != string::npos) && (j < 36)) {
                    temp = (readData).substr(0, findComma);
                    readData = readData.substr(findComma + 1);
                    double value = stod(temp);
                    if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                        simulatorMap.insert(
                                pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], value)));
                    } else {
                        if (mtx.try_lock()) {
                            simulatorMap.find(xmlDetails[j])->second->setValue(value);
                            mtx.unlock();
                        }

                    }
                    findComma = (readData).find_first_of(",");
                    j++;
                    if ((j == 35) && (findComma == string::npos) && (readData != "")) {
                        double value = stod(readData);
                        readData = "";
                        if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                            simulatorMap.insert(
                                    pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], value)));
                        } else {
                            if (mtx.try_lock()) {
                                simulatorMap.find(xmlDetails[j])->second->setValue(value);
                                mtx.unlock();
                            }
                        }
                        j++;
                    }
                }
                index = s.find_first_of("\n");
            }
            //what remains in s
            sEnd = s;
            s = "";
        }
    }
    return;
}

void OpenDataServerCommand::simulatorMapCreate(int client_socket) {
//reading from client
    int j = 0;
    int n = 0;
    char buffer[1024] = "";
    string readData = "";
    string temp = "";
    if (read(client_socket, buffer, 1024) > 0) {
        //convert char array to string
        string s = "";
        for (int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\0') {
                break;
            }
            s = s + buffer[i];
        }
        size_t index = s.find_first_of("\n");
        //s = s.substr(index + 1);
        //size_t index1 = s.find_first_of("\n");
        readData = (s).substr(0, index);
        size_t findComma = (readData).find_first_of(",");
        while ((findComma != string::npos) && (j < 36)) {
            temp = (readData).substr(0, findComma);
            readData = readData.substr(findComma + 1);
            double value = stod(temp);
            if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                simulatorMap.insert(pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], value)));
            }
            findComma = (readData).find_first_of(",");
            j++;
            if ((j == 35) && (findComma == string::npos) && (readData != "")) {
                double value = stod(readData);
                readData = "";
                if (simulatorMap.find(xmlDetails[j]) == simulatorMap.end()) {
                    simulatorMap.insert(pair<string, Variable *>(xmlDetails[j], new Variable(xmlDetails[j], value)));
                }
                j++;
            }
        }
    }
    return;
}
