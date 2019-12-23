//
// Created by amittulman on 16/12/2019.
//

#include "connectCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#include "dataManager.h"
#include "ex1.h"
#import <sstream>

using namespace std;

int connectCommand::execute (vector<string> vecClient) {
  dataManager* data = dataManager::getInstance();
  this->ipClient = vecClient.at(1);
  this->portClient = vecClient.at(2);

  Interpreter* i1 = new Interpreter();
  string varList = data->createSetVarString();
  i1->setVariables(varList);
  Expression* portExp = i1->interpret(portClient);
  int calculatrePort = portExp->calculate();
  int portNum = calculatrePort;
  delete(i1);

  data->clientThread = thread (openClient, this->ipClient, to_string(portNum));
  data->clientThread.detach();
  //openClient(vecClient.at(0),vecClient.at(1));
/*  thread t2(openClient, vecClient.at(0),vecClient.at(1));
  t2.join();*/
  return 3;
}


int openClient(string ip, string port) {
  dataManager *data = dataManager::getInstance();

  const char *cstr = data->cleanString(ip).c_str();

  int portNum = stoi(port);
  //create socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    //error
    std::cerr << "CLIENT: Could not create a socket" << std::endl;
    return -1;
  }

  //We need to create a sockaddr obj to hold address of server
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;//IP4
  address.sin_addr.s_addr = inet_addr(cstr);  //the localhost address
  address.sin_port = htons(portNum);
  //we need to convert our number (both port & localhost)
  // to a number that the network understands.

  // Requesting a connection with the server on local host with port 8081
  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    std::cerr << "CLIENT: Could not connect to host server" << std::endl;
    return -2;
  } else {
    std::cout << "CLIENT: Client is now connected to server" << std::endl;
  }

  std::cout << "CLIENT: client after connect " << std::endl;


    //if here we made a connection
while(data->flagFirstData == 0){
int i;
}

  while (true) {
    if (data->mtxFirstData.try_lock()) {

      while (!data->commandQueue.empty()) { //there are commands inside
        string popS = data->commandQueue.front();
        std::cout << "POPPED: " << popS << std::endl;

        data->commandQueue.pop();
        int messageLen = popS.length();
        int messageSize = popS.size();

/*        char massage[messageSize];
        int i;
        for (i = 0; i < messageSize; i++) {
          massage[i] = popS[i];
        }*/
        string temp = popS;
        char massage[1024];
        strcpy(massage, temp.c_str());
        int messageStrLen = strlen(massage);

        int is_sent = send(client_socket, massage, strlen(massage), 0);
        if (is_sent == -1) {
          std::cout << "CLIENT: Error sending message" << std::endl;
        } else {
          std::cout << "CLIENT: " << massage << std::endl;
        }

      }
      //char hello[] = "set controls/flight/rudder 1\r\n";
/*      int is_sent = send(client_socket, massage, strlen(hello), 0);
      if (is_sent == -1) {
        std::cout << "CLIENT: Error sending message" << std::endl;
      } else {
        std::cout << "CLIENT: RUDDER 1 SENT" << std::endl;
      }*/
      //sleep(1.5);
      //char hello2[] = "set controls/flight/rudder -1\r\n";

/*      int is_sent2 = send(client_socket, hello2, strlen(hello2), 0);
      if (is_sent2 == -1) {
        std::cout << "CLIENT: Error sending message" << std::endl;
      } else {
        std::cout << "CLIENT: RUDDER -1 SENT" << std::endl;
      }
      sleep(1.5);*/
      data->mtxFirstData.unlock();
    }
  }
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    //std::cout<<buffer<<std::endl;


  close(client_socket);
}

