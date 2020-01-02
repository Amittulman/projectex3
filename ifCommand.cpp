//
// Created by amittulman on 19/12/2019.
//

#include "ifCommand.h"
#include "Parser.h"
#include "dataManager.h"
#include "ex1.h"
int ifCommand::execute(vector<string> vec) {
  int i = 0;
  dataManager *data = dataManager::getInstance();
  vector<string> newVector;
  //push the commands that in the scope to new vector
  while (vec.at(i) != "}") {
    if (i > 2) {
      newVector.push_back(vec.at(i));
    }
    i++;
  }
  string s =vec.at(1);
  s = data->cleanString(s);
  //send to function to check the condition
  bool cond = condition1(s);
  Parser* par;
  if (cond) {
    par = new Parser(newVector);
    par->parse();
  }
  //delete(par);
  return i + 1;
}

//function for check the condition
bool condition1(string s){
  size_t prevPos = 0, position, position2;
  if (position = s.find("==") != string::npos) {
    pair<float,float> condExpressions = calculateCondition1(s, "==", 2);
    if (condExpressions.first == condExpressions.second)
      return true;
    else return false;
  }
  else if (position = s.find("<=") != string::npos) {
    pair<float,float> condExpressions = calculateCondition1(s, "<=", 2);
    if (condExpressions.first <= condExpressions.second)
      return true;
    else return false;
  }
  else if (position = s.find(">=") != string::npos) {
    pair<float,float> condExpressions = calculateCondition1(s, ">=", 2);
    if (condExpressions.first >= condExpressions.second)
      return true;
    else return false;
  }
  else if (position = s.find("!=") != string::npos) {
    pair<float,float> condExpressions = calculateCondition1(s, "!=", 2);
    if (condExpressions.first != condExpressions.second)
      return true;
    else return false;

  }  else if (position = s.find("<") != string::npos) {
    pair<float,float> condExpressions = calculateCondition1(s, "<", 1);
    if (condExpressions.first < condExpressions.second)
      return true;
    else return false;

  }
  else if (position = s.find(">") != string::npos) {
    pair<float,float> condExpressions = calculateCondition1(s, ">", 1);
    if (condExpressions.first > condExpressions.second)
      return true;
    else return false;

  }
}

pair<float, float> calculateCondition1(string s, string exp, int charsNumber){
  dataManager *data = dataManager::getInstance();
  int position = s.find(exp);
  //SY for condition
  string left = s.substr(0, position);
  string right = s.substr(position+charsNumber, s.length()-position-charsNumber);
  Interpreter* i1 = new Interpreter();
  string varList = data->createSetVarString();
  i1->setVariables(varList);
  Expression* exp3 = i1->interpret(left);
  float leftResult = exp3->calculate();
  delete(i1);
  delete(exp3);
  Interpreter* i2 = new Interpreter();
  i2->setVariables(varList);
  Expression* exp2 = i2->interpret(right);
  float rightResult = exp2->calculate();
  delete(i2);
  delete(exp2);
  return pair<float,float>(leftResult,rightResult);
}
