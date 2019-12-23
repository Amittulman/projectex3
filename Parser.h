//
// Created by amittulman on 16/12/2019.
//

#ifndef PROJECTEX3__PARSER_H_
#define PROJECTEX3__PARSER_H_
#include "Command.h"
#include <unordered_map>

class Parser {
 private:
  vector<string> lexVector;
 public:
  Parser(vector<string> vecLexer) {
    this->lexVector = vecLexer;
  }
   ~Parser() {
    delete (this);
  }
  void parse();
};

#endif //PROJECTEX3__PARSER_H_
