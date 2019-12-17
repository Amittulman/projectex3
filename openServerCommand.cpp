//
// Created by amittulman on 16/12/2019.
//

#include "openServerCommand.h"
#include "server.h"
#include <vector>
#include "dataManager.h"


using namespace std;

int openServerCommand::execute (vector<string> vecServer) {
  server* curServer = new server();
  curServer->openServer(vecServer.at(0)); //open server

}