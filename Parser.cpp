//
// Created by amittulman on 16/12/2019.
//

#include "Parser.h"
#include "openServerCommand.h"
#include "connectCommand.h"

using namespace std;

void Parser::parse() {
  commandsMap.insert(pair<string,Command*>("openDataServer",new openServerCommand()));
  commandsMap.insert(make_pair("openDataServer",new connectCommand()));
/*  commandsMap.insert(make_pair("openDataServer",new defineVarCommand()));
  commandsMap.insert(make_pair("openDataServer",new whileCommand()));
  commandsMap.insert(make_pair("openDataServer",new ifCommand()));
  commandsMap.insert(make_pair("openDataServer",new defineVarCommand()));
  commandsMap.insert(make_pair("openDataServer",new printCommand()));
  commandsMap.insert(make_pair("openDataServer",new sleepCommand()));*/

}
