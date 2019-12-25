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

pair<float, float> calculateCondition1(string s, string exp, int charsNumber);
bool condition1(string s);

#endif //PROJECTEX3__IFCOMMAND_H_
