//
// Created by amittulman on 16/12/2019.
//

#ifndef PROJECTEX3__CONNECTCOMMAND_H_
#define PROJECTEX3__CONNECTCOMMAND_H_

#include "Command.h"

class connectCommand : public Command {
 public:
  int execute(vector<string>) override;
};

int openClient(string ip, string port);
string updateIP(string ip);

#endif //PROJECTEX3__CONNECTCOMMAND_H_
