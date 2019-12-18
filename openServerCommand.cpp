//
// Created by amittulman on 16/12/2019.
//

#include "openServerCommand.h"
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


using namespace std;

int openServerCommand::execute (vector<string> vecServer) {
  this->port = vecServer.at(0);
  //int responseCode = openServer();
  thread t1(openServer, port);
  t1.join();
  thread t2(serverLogic);

  t2.join();
  return 0;

}

int openServer(string port) {
  int portNum = stoi(port);
  //create socket
  dataManager *data = dataManager::getInstance();
  data->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (data->serverSocket == -1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
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
    std::cerr << "Could not bind the socket to an IP" << std::endl;
    return -2;
  }

  //making socket listen to the port
  if (listen(data->serverSocket, 5) == -1) { //can also set to SOMAXCON (max connections)
    std::cerr << "Error during listening command" << std::endl;
    return -3;
  } else {
    std::cout << "Server is now listening ..." << std::endl;
  }

  // accepting a client
  socklen_t addrlen = sizeof(sockaddr_in);
  data->clientSocket = accept(data->serverSocket, (struct sockaddr *) &address,
                             &addrlen);

  std::cout << "server after accept " << std::endl;

  if (data->clientSocket == -1) {
    std::cerr << "Error accepting client" << std::endl;
    return -4;
  }
}

int serverLogic(){
  dataManager *data = dataManager::getInstance();

  //close(socketfd); //closing the listening socket
  while(1) {
    //reading from client
    char buffer[1024] = {0};
    int valread = read(data->clientSocket, buffer, 1024);
    std::cout << buffer << std::endl;

    std::cout << "server after reading " << std::endl;
    sleep(1);
    std::cout << "server after reading " << std::endl;
    sleep(1);
    std::cout << "server after reading " << std::endl;



    //writing back to client
    char *hello = "Hello, I can hear you! \n";
    send(data->clientSocket, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n" << std::endl;
    //return 0;
  }

}