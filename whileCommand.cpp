//
// Created by amittulman on 19/12/2019.
//

#include <iostream>
#include "whileCommand.h"
#include "Parser.h"
#include "dataManager.h"
#include "ex1.h"
int whileCommand::execute(vector<string> vec) {
  dataManager *data = dataManager::getInstance();
  int i = 0;
  vector<string> newVector;
  string cleanS = data->cleanString(vec.at(1));
  while (vec.at(i) != "}") { //create vector with all commands
    if (i > 2) {
      newVector.push_back(vec.at(i));
    }
    i++;
  }

  // ########### check type of condition
  bool cond = condition(cleanS);
  Parser* parse=new Parser(newVector);

  while (cond) { //send to function to check the condition
    parse->parse();
    cond = condition(cleanS);
  }
  if (parse != NULL) {
    delete(parse);
  }
  return i + 1;
}

//this method check the condition and return TRUE or FALSE
static bool condition(string s) {
  size_t prevPos = 0, position, position2;
  if (position = s.find("==") != string::npos) {
    pair<float,float> condExpressions = calculateCondition(s, "==", 2);
    if (condExpressions.first == condExpressions.second)
      return true;
    else return false;
  }
  else if (position = s.find("<=") != string::npos) {
    pair<float,float> condExpressions = calculateCondition(s, "<=", 2);
    if (condExpressions.first <= condExpressions.second)
      return true;
    else return false;
  }
  else if (position = s.find(">=") != string::npos) {
    pair<float,float> condExpressions = calculateCondition(s, ">=", 2);
    if (condExpressions.first >= condExpressions.second)
      return true;
    else return false;
  }
  else if (position = s.find("!=") != string::npos) {
    pair<float,float> condExpressions = calculateCondition(s, "!=", 2);
    if (condExpressions.first != condExpressions.second)
      return true;
    else return false;

  }  else if (position = s.find("<") != string::npos) {
    pair<float,float> condExpressions = calculateCondition(s, "<", 1);
    if (condExpressions.first < condExpressions.second)
      return true;
    else return false;

    }
      else if (position = s.find(">") != string::npos) {
    pair<float,float> condExpressions = calculateCondition(s, ">", 1);
    if (condExpressions.first > condExpressions.second)

      return true;
    else return false;

  }

  }

  //this method calculate the condition and return the values in pair
  static pair<float, float> calculateCondition(string s, string exp, int charsNumber){
    dataManager *data = dataManager::getInstance();
    int position = s.find(exp);
    //SY for the condition of the while
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
