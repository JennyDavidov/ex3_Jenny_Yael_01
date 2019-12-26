//
// Created by jenny on 19/12/2019.
//

#include "ConnectControlClientCommand.h"
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <arpa/inet.h>
#include <cstring>

using namespace std;
extern map<string, Variable *> simulatorMap;
extern map<string, Variable *> flyMap;


int ConnectControlClientCommand::execute(string *str, Interpreter *interpreter) {
    openClient(str, interpreter);
    return 3;
}

ConnectControlClientCommand::ConnectControlClientCommand() {}

void ConnectControlClientCommand::openClient(string *str, Interpreter *interpreter) {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        cerr << "Socket Failed" << endl;
        exit(-1);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    str += 1;
    (*str).erase((*str).length() - 1);
    (*str).erase(0, 1);
    address.sin_addr.s_addr = inet_addr(reinterpret_cast<const char *>((*str).c_str()));
    str += 1;
    unsigned short port;
    if (str->find_first_of("+-/*") != string::npos) {
        Expression *ex = interpreter->interpret(*str);
        port = ex->calculate();
    } else {
        port = stod(*str);
    }
    address.sin_port = htons(port);

    // Requesting a connection with the server on local host with port
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        exit(-1);
    } else {
        std::cout << "Client is now connected to server" << std::endl;
    }
    thread clientThread(sendToSimulator, client_socket);
    clientThread.detach();
    close(client_socket);
    return;
}

void ConnectControlClientCommand::sendToSimulator(int client_socket) {
    while (!parserDone) {
        if (message != NULL) {
            int is_sent = send(client_socket, message, strlen(message), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } else {
                std::cout << "Hello message sent to server" << std::endl;
            }
            message = NULL;
        }
    }
}

