//
// Created by amittulman on 19/12/2019.
//

#include "sleepCommand.h"
#include "ex1.h"
#include "dataManager.h"
#include <unistd.h>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
int sleepCommand::execute(vector<string> vec) {
  dataManager* data = dataManager::getInstance();
  Interpreter* i1 = new Interpreter();
  string varList = data->createSetVarString();
  i1->setVariables(varList);
  Expression* exp = i1->interpret(vec.at(1));
  double timeToSleep = exp->calculate();
  delete(i1);
  std::chrono::milliseconds duration((int)timeToSleep);
  std::this_thread::sleep_for(duration);
  return 2;
}

