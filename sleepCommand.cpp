//
// Created by amittulman on 19/12/2019.
//

#include "sleepCommand.h"
#include <unistd.h>

int sleepCommand::execute(vector<string> vec) {
  if (isParam(vec.at(1))) { // sleep(400)
    sleep(stoi(vec.at(1)));
  } else { //sleep(20+rudder)



  }

  return 2;
}
bool sleepCommand::isParam(string line) {
  char* p;
  strtol(line.c_str(), &p, 10);
  return *p == 0;
}
