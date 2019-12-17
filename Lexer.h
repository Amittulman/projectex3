//
// Created by amittulman on 16/12/2019.
//

#ifndef PROJECTEX3__LEXER_H_
#define PROJECTEX3__LEXER_H_

#include <unordered_map>
#include <list>
#include <fstream>
#include <functional>
#include <vector>

using namespace std;

class Lexer {
 public:
  static vector<string> split(string s);
};

#endif //PROJECTEX3__LEXER_H_
