//
// Created by amittulman on 18/12/2019.
//

#ifndef PROJECTEX3__DEFINEVARCOMMAND_H_
#define PROJECTEX3__DEFINEVARCOMMAND_H_

#include "defineVarCommand.h"

using namespace std;


class defineVarCommand : public Command {
 public:
  int execute(vector<string>) override;
};

#endif //PROJECTEX3__DEFINEVARCOMMAND_H_
