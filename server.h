//
// Created by amittulman on 16/12/2019.
//

#ifndef PROJECTEX3__SERVER_H_
#define PROJECTEX3__SERVER_H_
#include <string>
#include <string.h>


using namespace std;

class server {
 public:
  string port;
  server(string port1) {
    this->port = port1;
  }
  int openServer();
};
#endif //PROJECTEX3__SERVER_H_