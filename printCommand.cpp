//
// Created by amittulman on 19/12/2019.
//

#include <iostream>
#include "printCommand.h"
#include "dataManager.h"
int printCommand::execute(vector<string> vec) {
  if (vec.at(1)[0] == '\"') { //print string
    int size = vec.at(1).size();
    string newS = vec.at(1).substr(1,size - 2);
    std::cout << vec.at(1) << std::endl;
    return 2;
  } else { //print expression
    dataManager *data = dataManager::getInstance();
    if (data->progMap.at(vec.at(1)) != NULL) { // print(rudder)
      double value = data->progMap.at(vec.at(1))->val;
      std::cout << value << std::endl;
      return 2;
    } else { //print(rudder+(5-2))


      return 2;
    }
  }
}
