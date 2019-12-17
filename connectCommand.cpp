//
// Created by amittulman on 16/12/2019.
//

#include "connectCommand.h"
#include "client.h"

using namespace std;

int connectCommand::execute (vector<string> vecClient) {
  client* curClient = new client();
  curClient->openClient(vecClient.at(0),stoi(vecClient.at(1)));
  return 2;
}