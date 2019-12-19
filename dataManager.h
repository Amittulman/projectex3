//
// Created by amittulman on 17/12/2019.
//

#ifndef PROJECTEX3__DATAMANAGER_H_
#define PROJECTEX3__DATAMANAGER_H_

#include "server.h"
#include "client.h"
#include "varData.h"
#include "Command.h"
#include <map>
#include <unordered_map>
#include <thread>
#include <mutex>
using namespace std;

class dataManager {
 private:
  dataManager() {
    initializerMaps();
 }
 public:
  static dataManager* dataInstance;
  unordered_map<string,varData*> progMap;
  unordered_map<string,varData*> simMap;
  unordered_map<string,Command*> commandsMap;
  int serverSocket;
  int clientSocket;
  int flagFirstData = 0;
  mutex mtxVar;
  mutex mtxFirstData;
  thread serverThread;
  thread clientThread;
  void initializerMaps();

  static dataManager* getInstance() {
    if (!dataInstance) {
      dataInstance = new dataManager();
    }
    return dataInstance;
  }

/*  static void initialize() {
    dataInstance = NULL;
  }*/

};

#endif //PROJECTEX3__DATAMANAGER_H_