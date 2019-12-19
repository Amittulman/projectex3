//
// Created by amittulman on 19/12/2019.
//

#ifndef PROJECTEX3__PRINTCOMMAND_H_
#define PROJECTEX3__PRINTCOMMAND_H_

#include "Command.h"
class printCommand : public Command{
 public:
  int execute(vector<string> vec) override;
};

#endif //PROJECTEX3__PRINTCOMMAND_H_
