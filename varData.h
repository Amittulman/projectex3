//
// Created by amittulman on 17/12/2019.
//

#ifndef PROJECTEX3__VARDATA_H_
#define PROJECTEX3__VARDATA_H_

#include <string>

using namespace std;

class varData {
 public:
  string sim;
  double val;
  int direction;
  varData(string sim1, double value, int dirc) {
    this->sim = sim1;
    this->val = value;
    this->direction = dirc;
  }
};

#endif //PROJECTEX3__VARDATA_H_
