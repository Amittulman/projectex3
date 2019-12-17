//
// Created by amittulman on 16/12/2019.
//

#include <string>
#include <vector>
#ifndef PROJECTEX3__COMMAND_H_
#define PROJECTEX3__COMMAND_H_

using namespace std;

class Command {
 public:
  virtual int execute(vector<string> stringVect) = 0;
  ~Command(){};

};

#endif //PROJECTEX3__COMMAND_H_