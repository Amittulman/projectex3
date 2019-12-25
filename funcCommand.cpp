//
// Created by amittulman on 25/12/2019.
//

#include "funcCommand.h"
#include "dataManager.h"
#include "Parser.h"
#include "string"
#include "ex1.h"

// $func func(var x){
//  0     1     2
int funcCommand::execute(vector<string> vec) {
  dataManager *data = dataManager::getInstance();
  vector<string> funcVec;
  int position;
  string varName;
  if (vec.at(2).find(" ") != string::npos) {
    position = vec.at(2).find(" ");
    varName = vec.at(2).substr(position+1,vec.at(2).length()-position-1);
  }

  data->progMap.insert(pair<string, varData *>(varName, new varData("", 0,0)));
  int i = 4;
  funcVec.push_back(varName);
  int par = 1;
  while (1){
    if(vec.at(i)=="{")
      par += 1;
    else if(vec.at(i)=="}")
      par -= 1;
    funcVec.push_back(vec.at(i));
    if (par == 1 && vec.at(i)=="}")
      break;
    i++;
  }
  data->funcMap.insert(pair<string,vector<string>>(vec.at(1),funcVec));
  return i+2;
}
// func(rudder)
int funcIt(vector<string> vec){ // vec = {func, rudder/digits}
  dataManager *data = dataManager::getInstance();
  string VarName = data->funcMap[vec.at(0)].at(0); // funcMap = {funcName:(VarName, command1...)}


  // Translate the function argument to a value

  //Update the value of the function argument
  if (!data->progMap.count(vec.at(1))){
    Interpreter* i1 = new Interpreter();
    string varList = data->createSetVarString();
    i1->setVariables(varList);
    Expression* exp = i1->interpret(vec.at(1));
    float value = exp->calculate();
    data->progMap[VarName]->val = value;
    delete(i1);
    delete(exp);
  } else{
    data->progMap[VarName] = data->progMap[(vec.at(1))];
  }

  //Creata a vector that contains only the function commands
  vector<string> newVec;
/*  vector<string> funcVec = data->funcMap[vec.at(0)];
  for(int i = 1 ; i< funcVec.size(); i++){
    newVec.push_back(funcVec.at(i));
  }*/
  for(int i = 1 ; i< data->funcMap[vec.at(0)].size(); i++){
    newVec.push_back(data->funcMap[vec.at(0)].at(i));
  }

  //Send all the commands to parser (execute function)
  Parser* par = new Parser(newVec);
  par->parse();


  delete(par);
  return 2;
}

