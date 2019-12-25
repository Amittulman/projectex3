//
// Created by amittulman on 16/12/2019.
//

#include "Parser.h"
#include "openServerCommand.h"
#include "connectCommand.h"
#include "dataManager.h"

using namespace std;

void Parser::parse() {
  dataManager* data = dataManager::getInstance();
  if (data == NULL){
    int j;
  }
  vector<string> lex = this->lexVector;
  int vecSize = lex.size();
  int index = 0;
  while (index < vecSize) {
    Command* c = data->commandsMap[lex.at(index)];
    if (c != NULL) {
      vector<string> newVec;
      for (int i = index; i < vecSize; i++) {
        newVec.push_back(lex[i]);
      }
      index += c->execute(newVec);
    } else { //not in tha commandMap : warp = 5
      Command* c = data->commandsMap["var"];
      vector<string> newVec;
      for (int i = index; i < vecSize; i++) {
        newVec.push_back(lex[i]);
      }
      index += c->execute(newVec);
    }
  }
}