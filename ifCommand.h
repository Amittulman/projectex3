//
// Created by amittulman on 19/12/2019.
//

#ifndef PROJECTEX3__IFCOMMAND_H_
#define PROJECTEX3__IFCOMMAND_H_

#include "Command.h"
class ifCommand: public Command {
 public:
  int execute(vector<string> vec) override;
};

#endif //PROJECTEX3__IFCOMMAND_H_
