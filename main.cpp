//
// Created by amittulman on 17/12/2019.
//
#include "dataManager.h"
#include "client.h"
#include "server.h"
#include "connectCommand.h"
#include "dataManager.h"
#include "Lexer.h"
#include "Parser.h"
#include "openServerCommand.h"
#include "varData.h"

int main() {
  string s = "/home/amittulman/CLionProjects/projectex3/fly.txt";
 /* vector<string> vecLexer = Lexer::split(s);
  dataManager* data = dataManager::getInstance();  //create control manager*/
  openServerCommand* s1 = new openServerCommand();
  vector<string> vec = {"5400"};
  s1->execute(vec);
};
