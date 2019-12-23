//
// Created by amittulman on 19/12/2019.
//

#ifndef PROJECTEX3__SLEEPCOMMAND_H_
#define PROJECTEX3__SLEEPCOMMAND_H_

#include "Command.h"
class sleepCommand : public Command {
 public:
  int execute(vector<string> vec) override;
};

#endif //PROJECTEX3__SLEEPCOMMAND_H_
