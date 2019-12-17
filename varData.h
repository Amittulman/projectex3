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
  varData(string sim1, double value) {
    this->sim = sim1;
    this->val = value;
  }
};

#endif //PROJECTEX3__VARDATA_H_
