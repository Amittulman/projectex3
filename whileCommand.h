//
// Created by amittulman on 19/12/2019.
//

#ifndef PROJECTEX3__WHILECOMMAND_H_
#define PROJECTEX3__WHILECOMMAND_H_

#include "Command.h"
class whileCommand : public Command{
 public:
  int execute(vector<string> vec) override;
};

#endif //PROJECTEX3__WHILECOMMAND_H_
