//
// Created by amittulman on 16/12/2019.
//

#ifndef PROJECTEX3__OPENSERVERCOMMAND_H_
#define PROJECTEX3__OPENSERVERCOMMAND_H_

#include "Command.h"
class openServerCommand : public Command {
 public:
  int execute(vector<string>) override;
  void execute();
};

#endif //PROJECTEX3__OPENSERVERCOMMAND_H_
