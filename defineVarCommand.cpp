//
// Created by amittulman on 18/12/2019.
//



#include "connectCommand.h"
#include "client.h"
#include "defineVarCommand.h"
#include "dataManager.h"
#include <sstream>

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
  if (vecVar.at(0) == "var"){ //initialize new var for map
    if (vecVar.at(3) == "sim") { // got sim from text
      string s = vecVar.at(4);
      s = data->cleanString(s);
      varData *curVar = data->simMap[s];
      data->progMap.insert(pair<string, varData *>(vecVar.at(1), curVar));
      return 5;
    }
    if (data->progMap[vecVar.at(3)] != NULL) {
      varData *curVar1 = new varData(NULL, data->getValue(vecVar.at(3), 0));
      data->progMap.insert(pair<string, varData *>(vecVar.at(1), curVar1));
    } else { // value is not in the map
      varData* curVar3 = new varData(NULL, stod(vecVar.at(4))); // take care of expression
      data->progMap.insert(pair<string, varData *>(vecVar.at(1), curVar3));
    }
  } else if (vecVar.at(0) != "var"){     // rudder = 3
    //take care of expression
    data->setVal(vecVar.at(0),stod(vecVar.at(2)), 0);

    ostringstream oss;
    oss << "set " << data->getSim(vecVar.at(0)) << " " << to_string((float)data->getValue(vecVar.at(0), 0)) << "\r\n";
    data->commandQueue.push(oss.str());
    std::cout << "PUSHED: " << oss.str() << std::endl;
    return 3;
    // ########### mutex?
  }

}

