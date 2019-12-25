//
// Created by amittulman on 17/12/2019.
//

#ifndef PROJECTEX3__DATAMANAGER_H_
#define PROJECTEX3__DATAMANAGER_H_

#include "varData.h"
#include "Command.h"
#include <map>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <iostream>
#include <queue>
using namespace std;

class dataManager {
 private:
  dataManager() {
    initializerMaps();
 }
 public:
  static dataManager* dataInstance;
  unordered_map<string,varData*> progMap;
  unordered_map<string,Command*> commandsMap;
  unordered_map<string,vector<string>> funcMap;
  map<string,varData*> simMap;
  string simPath[36];
  int serverSocket;
  int clientSocket;
  int flagFirstData = 0;
  mutex mtxVal;
  mutex mtxDone;
  mutex mtxFirstData;
  thread serverThread;
  thread clientThread;
  queue<string> commandQueue;

  void initializerMaps();
  int done = 0;
  virtual ~dataManager();
  static dataManager* getInstance() {
    if (!dataInstance) {
      dataInstance = new dataManager();
    }
    return dataInstance;
  }

  int IsDone() {
    mtxDone.lock();
    double newDone = done;
    mtxDone.unlock();
    return newDone;
  }

  double getValue(string s, int sim) {
    mtxVal.lock();
    double val;
    if (sim == 1) { // search value by sim
      val = simMap[s]->val;
    } else { // search by var
      val = progMap[s]->val;
    }
    mtxVal.unlock();
    return val;
  }

  string getSim(string s) {
    string sim = progMap[s]->sim;
    return sim;
  }

  void setVal(string key, double val, int sim) {
    mtxVal.lock();
    if (sim == 1) {
      simMap[key]->val = val;

    } else {
      progMap[key]->val = val;
    }
    mtxVal.unlock();
    return;
  }

  static string cleanString(string ip) {
      int len = ip.length();
      string newIP = "";
      for (int i = 0; i < len; i++) {
        if (ip.at(i) == '\"')
          continue;
        else if (ip.at(i) == '\\')
          continue;
        else if (ip.at(i) == ' ')
          continue;
        newIP += ip.at(i);
      }
      if(newIP.at(0) == '/'){
        newIP = newIP.substr(1, newIP.length()-1);
      }
      return newIP;
    }

  string createSetVarString() {
    string curSet="";
    for (auto& it: this->progMap) {
      curSet += it.first + "=" + to_string(it.second->val) + ";";
    }
    curSet = curSet.substr(0, curSet.length() - 1);
    if (!curSet.compare("")){
      curSet = "$$$";
    }
    return curSet;
    }

};

#endif //PROJECTEX3__DATAMANAGER_H_