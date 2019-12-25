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


using namespace std;

int OpenDataServerCommand::execute(string *str, Interpreter *interpreter) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        exit(-1);
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    str += 1;
    unsigned short port;
    if (str->find_first_of("+-/*") != string::npos) {
        Expression* ex = interpreter->interpret(*str);
        port = ex->calculate();
    } else {
        port = stod(*str);
    }
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        exit(-1);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        exit(-1);
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        exit(-1);
    }

    close(socketfd); //closing the listening socket
    openServer(str,client_socket);
//    thread serverThread(openServer, str,client_socket);
//    serverThread.detach();

    return 2;
}

OpenDataServerCommand::OpenDataServerCommand() {}

void OpenDataServerCommand::openServer(string *str, int client_socket) {
    //reading from client
    int j = 0;
    int n=0;
    char buffer[1024];
    while(read(client_socket , buffer, 1024)>0) {
        vector<string> xmlDetails;
        xmlDetails = readingXml();
        string temp;
        for (int i = 0; i < sizeof(buffer); i++) {
            if (strcmp(",", reinterpret_cast<const char *>(buffer[i])) != 0) {
                temp = temp + buffer[i];
            } else {
                double value = stod(temp);
                simulatorMap.find(xmlDetails.at(j));
                Variable *obj = new Variable(xmlDetails.at(j), value);
                simulatorMap.insert(
                        pair<string, Variable *>(xmlDetails.at(j), reinterpret_cast<Variable *const>(&obj)));
                j++;
                str = 0;
            }
        }
    }
        //writing back to client
//    char *hello = "Hello, I can hear you! \n";
//    send(client_socket , hello , strlen(hello) , 0 );
//    std::cout<<"Hello message sent\n"<<std::endl;
        return;
    }
