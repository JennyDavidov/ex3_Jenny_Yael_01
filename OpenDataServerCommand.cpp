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


using namespace std;


int OpenDataServerCommand::execute(string *str) {
    int server_fd;
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    str += 1;
    unsigned short port = stod(*str);
    address.sin_port = port;
    //First step - Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        cerr << "Socket Failed" << endl;
        exit(-1);
    }
    //Second step - Bind
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Bind Failed" << endl;
        exit(-1);
    }
    if (listen(server_fd, 1) == -1) {
        cerr << "Listen Failed" << endl;
        exit(-1);
    }
    int client_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &address);
    if (client_socket < 0) {
        cerr << "Accept Failed" << endl;
        exit(-1);
    }
    thread serverThread(openServer, str,client_socket);
    serverThread.detach();
    close(client_socket);
    return 2;
}

OpenDataServerCommand::OpenDataServerCommand() {}

void OpenDataServerCommand::openServer(string *str, int client_socket) {
    //reading from client
    int j = 0;
    int n=0;
    char buffer[1024];
    while(read(client_socket , buffer, 1024)>0){
    vector<string> xmlDetails;
    xmlDetails = readingXml();
    string temp;
    for (int i = 0; i < sizeof(buffer); i++) {
        if (strcmp(",", reinterpret_cast<const char *>(buffer[i])) != 0) {
            temp = temp + buffer[i];
        } else {
            double value = stod(temp);
            simulatorMap.find(xmlDetails.at(j))
            Variable *obj = new Variable(xmlDetails.at(j), value);
            simulatorMap.insert(pair<string, Variable *>(xmlDetails.at(j), reinterpret_cast<Variable *const>(&obj)));
            j++;
            str=0;
        }
    }
    //writing back to client
//    char *hello = "Hello, I can hear you! \n";
//    send(client_socket , hello , strlen(hello) , 0 );
//    std::cout<<"Hello message sent\n"<<std::endl;
    return;
}