//
// Created by amittulman on 19/12/2019.
//

#include <iostream>
#include "printCommand.h"
#include "dataManager.h"
#include "ex1.h"
int printCommand::execute(vector<string> vec) {
  if (vec.at(1)[0] == '\"') { //print string
    int size = vec.at(1).size();
    string newS = vec.at(1).substr(1,size - 2);
    std::cout << vec.at(1) << std::endl;
    return 2;
  } else { //print expression
    dataManager *data = dataManager::getInstance();

    Interpreter* i1 = new Interpreter();
    string varList = data->createSetVarString();
    i1->setVariables(varList);
    Expression* printString = i1->interpret(vec.at(1));
    double intString = printString->calculate();
    delete(i1);

    std::cout << to_string(intString) << std::endl;
    return 2;

    }
  }

