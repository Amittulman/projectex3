//
// Created by amittulman on 16/12/2019.
//

#include "Parser.h"
#include "openServerCommand.h"
#include "connectCommand.h"
#include "dataManager.h"
#include "funcCommand.h"

using namespace std;

void Parser::parse() {
  dataManager* data = dataManager::getInstance();
  if (data == NULL){
    int j;
  }
  vector<string> lex = this->lexVector;
  int vecSize = lex.size();
  int index = 0;
  while (index < vecSize) { //iterate over the vector
    //try to catch the command from map
    Command* c = data->commandsMap[lex.at(index)];
    if (c != NULL) { //check if the command is exists
      vector<string> newVec;
      for (int i = index; i < vecSize; i++) {
        newVec.push_back(lex[i]);
      }
      index += c->execute(newVec); //jump in the vector after execute the command
    } else { //not in the commandMap : warp = 5 or function(var);
        if (lex.at(index+1) != "="){ //identify function
          cout<<"in func"<<endl;
          vector<string> newVec;
          for (int i = index; i < vecSize; i++) {
            newVec.push_back(lex[i]);
          }
          index+=funcIt(newVec);//jump in the vector after execute the command
        } else { //identify if var
        Command* c = data->commandsMap["var"];
        vector<string> newVec;
        for (int i = index; i < vecSize; i++) {
          newVec.push_back(lex[i]);
        }
        index += c->execute(newVec);//jump in the vector after execute the command
       }
   }
  }
}