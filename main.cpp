//
// Created by amittulman on 17/12/2019.
//
#include "dataManager.h"
#include "connectCommand.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc,char *argv[]) {
  string ss = argv[1];
  vector<string> vecLexer = Lexer::split(ss);
  Parser* par = new Parser(vecLexer);
  par->parse();
  dataManager* data = dataManager::getInstance();
  data->done = 1;
  delete(par);
  delete(data);
};
