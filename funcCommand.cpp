//
// Created by amittulman on 25/12/2019.
//

#include "funcCommand.h"
#include "dataManager.h"
#include "Parser.h"
#include "string"
#include "ex1.h"
//this method is responsible declaring function and store the function commands
int funcCommand::execute(vector<string> vec) {
  dataManager *data = dataManager::getInstance();
  vector<string> funcVec;
  int position;
  string varName;
  //split the declaration and save the name of the argument and store it
  if (vec.at(2).find(" ") != string::npos) {
    position = vec.at(2).find(" ");
    varName = vec.at(2).substr(position+1,vec.at(2).length()-position-1);
  }
  //insert the var name to the prog map
  data->progMap.insert(pair<string, varData *>(varName, new varData("", 0,0)));
  int i = 4;
  funcVec.push_back(varName);
  int par = 1;
  //check valid parantheses
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
  //store the func command in diffrent map for functions
  data->funcMap.insert(pair<string,vector<string>>(vec.at(1),funcVec));
  return i+2;
}


// func(rudder)
// this method run the function
int funcIt(vector<string> vec){ // vec = {func, rudder/digits}
  dataManager *data = dataManager::getInstance();
  string VarName = data->funcMap[vec.at(0)].at(0); // funcMap = {funcName:(VarName, command1...)}


  // Translate the function argument to a value

  //Update the value of the function argument
  if (!data->progMap.count(vec.at(1))){
    // SY
    Interpreter* i1 = new Interpreter();
    string varList = data->createSetVarString();
    i1->setVariables(varList);
    Expression* exp = i1->interpret(vec.at(1));
    float value = exp->calculate();
    data->progMap[VarName]->val = value;
    delete(i1);
    delete(exp);
  } else { //the var is not in the progmap
    data->progMap[VarName] = data->progMap[(vec.at(1))];
  }

  //Creata a vector that contains only the function commands
  vector<string> newVec;
  for(int i = 1 ; i< data->funcMap[vec.at(0)].size(); i++){
    newVec.push_back(data->funcMap[vec.at(0)].at(i));
  }

  //Send all the commands to parser (execute function)
  Parser* par = new Parser(newVec);
  par->parse();


  delete(par);
  return 2;
}

