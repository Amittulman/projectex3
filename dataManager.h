//
// Created by amittulman on 17/12/2019.
//

#ifndef PROJECTEX3__DATAMANAGER_H_
#define PROJECTEX3__DATAMANAGER_H_

#include "server.h"
#include "client.h"
#include "varData.h"
#include <map>
#include <unordered_map>
using namespace std;

class dataManager {
 private:
  static dataManager* dataInstance;
  dataManager() {
   initializerSimMap();
 }
 public:
  unordered_map<string,varData*> progMap;
  unordered_map<string,varData*> simMap;
  server* managerServer;
  client* managerClient;
  void initializerSimMap();

  static dataManager* getInstance() {
    if (dataInstance == NULL) {
      dataInstance = new dataManager();
    }
    return dataInstance;
  }

};

#endif //PROJECTEX3__DATAMANAGER_H_