//
// Created by amittulman on 18/12/2019.
//



#include "connectCommand.h"
#include "client.h"
#include "defineVarCommand.h"
#include "dataManager.h"

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#include <vector>

using namespace std;

int defineVarCommand::execute(vector<string> vecVar) {
  dataManager *data = dataManager::getInstance();
  int declaration = 0;
  if (vecVar.at(3) == "sim") { // got sim from text = declaration of var
    varData* curVar = new varData(vecVar.at(4), 0);
    data->progMap.insert(pair<string,varData*>(vecVar.at(1),curVar));
    data->simMap[vecVar.at(4)] = curVar;
    return 5;
  } else if (vecVar.at(0) == "var"){ //initialize new var for map
    if (data->progMap[vecVar.at(3)] != NULL) {
      varData *curVar1 = new varData(NULL, data->progMap[vecVar.at(3)]->val);
      data->progMap.insert(pair<string, varData *>(vecVar.at(1), curVar1));
    } else { // value is not in the map
      varData* curVar3 = new varData(NULL, stoi(vecVar.at(4))); // take care of expression
      data->progMap.insert(pair<string, varData *>(vecVar.at(1), curVar3));
    }
  } else { // rudder = 3
    data->progMap[vecVar.at(0)]->val = stoi(vecVar.at(2)); //take care of expression
    // ########### mutex?
  }
}