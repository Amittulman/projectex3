//
// Created by amittulman on 16/12/2019.
//

#ifndef PROJECTEX3__OPENSERVERCOMMAND_H_
#define PROJECTEX3__OPENSERVERCOMMAND_H_

#include "Command.h"
#include <vector>

class openServerCommand : public Command {
 private:
  string port;
 public:
  int execute(vector<string>) override;
};
int openServer(string port);

#endif //PROJECTEX3__OPENSERVERCOMMAND_H_
