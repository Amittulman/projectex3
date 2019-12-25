//
// Created by amittulman on 25/12/2019.
//

#ifndef PROJECTEX3__FUNCCOMMAND_H_
#define PROJECTEX3__FUNCCOMMAND_H_

#include "Command.h"
class funcCommand : public Command {
 public:
  int execute(vector<string>) override;
};

int funcIt(vector<string>);

#endif //PROJECTEX3__FUNCCOMMAND_H_
