//
// Created by amittulman on 16/12/2019.
//

#ifndef PROJECTEX3__PARSER_H_
#define PROJECTEX3__PARSER_H_
#include "Command.h"
#include <map>

class Parser {
 private:
  map<string,Command*> commandsMap;

 public:
  Parser() {
    this->commandsMap = {};
  }
  void parse();
};

#endif //PROJECTEX3__PARSER_H_
