//
// Created by amittulman on 16/12/2019.
//

#include "openServerCommand.h"
#include "connectCommand.h"
#include "server.h"
#include <vector>
#include <thread>
#include "dataManager.h"

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <mutex>
#include <cmath>
#include "Expression.h"
#include "ex1.h"

class openClient;
using namespace std;

int openServerCommand::execute (vector<string> vecServer) {
  dataManager* data = dataManager::getInstance();
  this->portServer = vecServer.at(1);
  //int responseCode = openServer();
  thread t1(openServer, this->portServer);
  t1.join();
  data->serverThread = thread (serverLogic);
  data->serverThread.detach();
  return 2;

}

int openServer(string port) {
  dataManager* data = dataManager::getInstance();
  data->mtxFirstData.lock();
  Interpreter* i1 = new Interpreter();
  string varList = data->createSetVarString();
  i1->setVariables(varList);
  Expression* portExp = i1->interpret(port);
  double calculatrePort = portExp->calculate();
  int portNum = (int)round(calculatrePort);
  delete(i1);
  //create socket
  data->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (data->serverSocket == -1) {
    //error
    std::cerr << "SERVER :Could not create a socket" << std::endl;
    return -1;
  }

  //bind socket to IP address
  // we first need to create the sockaddr obj.
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
  address.sin_port = htons(portNum);
  //we need to convert our number
  // to a number that the network understands.

  //the actual bind command
  if (bind(data->serverSocket, (struct sockaddr *) &address, sizeof(address)) == -1) {
    std::cerr << "SERVER :Could not bind the socket to an IP" << std::endl;
    return -2;
  }

  //making socket listen to the port
  if (listen(data->serverSocket, 5) == -1) { //can also set to SOMAXCON (max connections)
    std::cerr << "SERVER :Error during listening command" << std::endl;
    return -3;
  } else {
    std::cout << "SERVER :Server is now listening ..." << std::endl;
  }

  // accepting a client
  socklen_t addrlen = sizeof(sockaddr_in);
  data->clientSocket = accept(data->serverSocket, (struct sockaddr *) &address,
                             &addrlen);

  std::cout << "SERVER : server after accept " << std::endl;

  if (data->clientSocket == -1) {
    std::cerr << "SERVER : Error accepting client" << std::endl;
    return -4;
  }
}

int serverLogic(){
  dataManager *data = dataManager::getInstance();
  //close(socketfd); //closing the listening socket
  char buffer[1024] = {0};

  while(1) {
    //reading from client
    int valread = read(data->clientSocket, buffer, 1024);

    //std::cout <<"Data from sim: " << buffer << std::endl;

    //string val = to_string(data->simMap["instrumentation/gps/indicated-ground-speed-kt"]->val); // --------------------------------------------------- Debug -----------------
    //std::cout <<"speed: " << val << std::endl; // --------------------------------------------------- Debug -----------------

    if (data->flagFirstData == 0) {
      data->mtxFirstData.unlock();
    }
    data->flagFirstData = 1;  // first time information recieved
    splitDetails(buffer);




    //std::cout << "SERVER :server after reading " << std::endl;
    //sleep(1);
/*    std::cout << "SERVER :server after reading " << std::endl;
    sleep(1);
    std::cout << "SERVER :server after reading " << std::endl;*/



    //writing back to client
    //char *hello = "SERVER :Hello, I can hear you! \n";
    //send(data->clientSocket, hello, strlen(hello), 0);
  // std::cout << "SERVER :Hello message sent\n" << std::endl;
    //return 0;
  }
}

void splitDetails(string s) {
  dataManager *data = dataManager::getInstance();
  string temp = "";
  int i = 0;
  while ( s[i] != '\n' && s[i] != string::npos){
    temp += s[i];
  }
  temp+='\n';
  char str[1024];
  strcpy(str, temp.c_str());
  i = 0;
  char * pch;
  //printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str,",\n");
  while (pch != NULL)
  {
    int bindDirection = data->simMap[data->simPath[i]]->direction;
    if (bindDirection) { //The direction is from sim to program - update valudata->setVal(data->simPath[i], stod(currentValue), 1);
      data->setVal(data->simPath[i], stod(pch), 1);
    }
    i++;
    //printf ("%s\n",pch);
    pch = strtok (NULL, ",\n");
  }
/*
  size_t prevPos = 0, position, position2;
  int i = 0;
  //for (i = 0; i < 36; i++) {
  char str[1024];
  strcpy(str, temp.c_str());
  int messageStrLen = strlen(str);
    //char str[] ="";
    char * pch;
    char * p;
    //printf ("Splitting string \"%s\" into tokens:\n", str);
    pch = strtok (str,"\n");
    while (pch != NULL)
    {
      //printf ("%s\n",pch);
      p = strtok (pch, ",");
      int bindDirection = data->simMap[data->simPath[i]]->direction;
      if (bindDirection) { //The direction is from sim to program - update valudata->setVal(data->simPath[i], stod(currentValue), 1);
        data->setVal(data->simPath[i], stod(pch), 1);
      }
      i++;
    }*/
 // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    /*if (i < 35) {
      position = s.find(',');
      string currentValue = s.substr(prevPos, position);
      s = s.substr(position + 1, s.length() - position - 1);
      int bindDirection = data->simMap[data->simPath[i]]->direction;
      if (bindDirection) { //The direction is from sim to program - update value
       data->setVal(data->simPath[i], stod(currentValue), 1);
             }
           } else {
             position = s.find('\n');
             string currentValue = s.substr(prevPos, position);
             s = s.substr(position + 1, s.length() - position - 1);
             int bindDirection = data->simMap[data->simPath[i]]->direction;
             if (bindDirection) { //The direction is from sim to program - update value
               data->setVal(data->simPath[i], stod(currentValue), 1);
             }
    }*/
  //}
}
