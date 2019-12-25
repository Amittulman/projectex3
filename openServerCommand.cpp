//
// Created by amittulman on 16/12/2019.
//

#include "openServerCommand.h"
#include "connectCommand.h"
#include <vector>
#include <thread>
#include "dataManager.h"

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
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

    if (data->flagFirstData == 0) {
      data->mtxFirstData.unlock();
    }
    data->flagFirstData = 1;  // first time information recieved
    splitDetails(buffer, valread);


    if (data->IsDone()) {
      close(data->serverSocket);
      break;
    }
  }
}

void splitDetails(string s, int valread) {

dataManager *data = dataManager::getInstance();
if (s[0] == ',') {
  s = s.substr(1,s.length()-1);
}
string cutS = "";
string copyS = s;
int copLen = copyS.length();
int i =0;
while (copyS[i] != '\n') {
  cutS += copyS[i];
  i++;
}
  int cutlennnn = cutS.length();

int counter = 0;
while (cutS.size() > 0 && counter < 36) {
int cutLen =  cutS.length();
  size_t found = cutS.find(",");
  if (found != std::string::npos) {
    string toList = cutS.substr(0, found);
    string newString = cleanString(toList);
    int bindDirection = data->simMap[data->simPath[counter]]->direction;
    if (newString == "") {
      newString = "0";
    }
    if (bindDirection)  //The direction is from sim to program - update value
      data->setVal(data->simPath[counter], stod(newString), 1);
    // ----------------------------Debug-------------------------------
/*    if (counter == 3) {
      cout<< "heading in server:" << newString << endl;
      cout<< "heading in server after stod:" << stod(newString) << endl;
      cout<< "heading in progmap:" << data->progMap["heading"]->val << endl;
      cout<< "the sim:" << data->simPath[counter] << endl;

    }*/
    counter++;
    cutS = cutS.substr(found + 1, cutS.size());
    } else {
      string toList = cutS.substr(0, cutS.length() -1 );
      int bindDirection = data->simMap[data->simPath[counter]]->direction;
      string newString = cleanString(toList);
      if (newString == "") {
        newString = "0";
      }

    if (bindDirection) { //The direction is from sim to program - update value
        data->setVal(data->simPath[counter], stod(newString), 1);
        counter++;
        //break;
      } else {
      counter++;
    }
    }
  }
  return;


}

string cleanString(string ip)
{
  int len = ip.length();
  string newIP = "";
  for (int i = 0; i < len; i++) {
    if (ip.at(i) == '-')
      newIP += ip.at(i);
    else if (ip.at(i) == '.')
      newIP += ip.at(i);
    else if (isdigit(ip.at(i)))
      newIP += ip.at(i);
    continue;  }

  return newIP;
}




