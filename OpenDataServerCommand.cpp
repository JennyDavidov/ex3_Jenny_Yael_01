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
#include "Expression.h"
#include "interpreter.h"

using namespace std;


int OpenDataServerCommand::execute(string *str, Interpreter* interpreter) {
    thread serverThread(openServer,str, interpreter);
    serverThread.detach();
    return 2;
}

OpenDataServerCommand::OpenDataServerCommand() {}

void OpenDataServerCommand::openServer(string *str, Interpreter* interpreter) {
    int server_fd;
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    str += 1;
    unsigned short port;
    if (str->find_first_of("+-/*") != string::npos) {
        Expression* ex = interpreter->interpret(*str);
        port = ex->calculate();
    } else {
        port = stod(*str);
    }
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
    //closing the listening socket
    close(client_socket);

    //reading from client
    char buffer[1024] = {0};
    int valread = read( client_socket , buffer, 1024);
    std::cout<<buffer<<std::endl;

    //writing back to client
//    char *hello = "Hello, I can hear you! \n";
//    send(client_socket , hello , strlen(hello) , 0 );
//    std::cout<<"Hello message sent\n"<<std::endl;
    return;
}