//
// Created by amittulman on 06/11/2019.
//

#include "ex1.h"
#include <iostream>
#include "Expression.h"
#include <map>
#include "stdlib.h"
#include <bits/stdc++.h>
#include <string.h>
#include <deque>

using namespace std;

double Variable::calculate() {
  return this->num;
}

Variable& Variable::operator--() {
  this->num -= 1;
  return *this;
}

Variable& Variable::operator++() {
  this->num += 1;
  return *this;
}

Variable& Variable::operator+=(double) {
  this->num += this->num;
  return *this;
}

Variable& Variable::operator-=(double) {
  this->num += this->num;
  return *this;
}

Variable& Variable::operator--(int) {

  this->num-=1;
  return *this;
}

Variable& Variable::operator++(int) {
  this->num+=1;
  return *this;
}

double Value::calculate() {
  return this->val;
}

double UPlus::calculate() {
  return this->expr1->calculate();
}

double UMinus::calculate() {
  return this->expr1->calculate() * -1;
}

double Plus::calculate() {
  return leftExp->calculate() + rightExp->calculate();
}

double Minus::calculate() {
  return leftExp->calculate() - rightExp->calculate();
}

double Mul::calculate() {
  return leftExp->calculate() * rightExp->calculate();
}
double Div::calculate() {
  return leftExp->calculate() / rightExp->calculate();
}

void Interpreter::setVariables(string str) {
  string word = "";
  string leftSide = "";
  for (auto x : str) {
    if (x == ';') {
      string var = "";
      for (auto y : word) {
        if ( y == '=') {
          leftSide = var;
          //check if valid
          if (isdigit(leftSide[0])) {
            throw ("wrong input! variable cant start with a number");
          }
          for(char c: leftSide){
            if(!(((c >= 'a') &&(c<='z'))|| ((c>='A')&&(c<='z')) || ((c>= '0')&& (c<='9')) || (c=='_')))
              throw ("Bad input for variable! ");
          }
          var = "";
        } else {
          var = var + y;
        }
      }
      //check
      int minusTimes = 0;
      int sumDots = 0;
      for(char c2 : var){
        if (c2 == '.'){
          sumDots++;
        }
        if (c2 == '-') {
          minusTimes++;
        }
      }
      if (sumDots > 1) {
        throw ("wrong input! value need only one dot");
      }
      int flag1 = 0;
      if (minusTimes == 1) {
        if (var[0] == '-') {
          flag1 = 1;
        } else {
          flag1 = 4;
        }
      }
      for(char c3 : var){
        if (((!isdigit(c3)) && (c3 != '.')) ||(flag1 == 4) ){
          throw ("wrong input! value need only numbers");
        }
      }
      const char * c = var.c_str();
      if (this->map1.count(leftSide)) {
        this->map1.find(leftSide)->second = strtod(c, NULL);
      }
      this->map1[leftSide] = strtod(c,NULL);
      word = "";
    } else {
      word = word + x;
    }
  }
  string var = "";
  for (auto y : word) {
    if ( y == '=') {
      leftSide = var;
      var = "";
    } else {
      var = var + y;
    }
  }

  const char * c = var.c_str();
  // check if the value valid
  int sumDots = 0;
  int minusTimes = 0;
  for(char c2 : var){
    if (c2 == '.'){
      sumDots++;
    }
    if (c2 == '-') {
      minusTimes++;
    }
  }
  if (sumDots > 1) {
    throw ("wrong input! value need only one dot");
  }
  int flag = 0;
  if (minusTimes > 1) {
    throw ("wrong input! value need only one dot and numbers");
  }
  if (minusTimes == 1) {
    if (var[0] == '-') {
      flag = 1;
    } else {
      flag = 4;
    }
  }
  for(char c3 : var){
    if ((!isdigit(c3)) && (c3 != '.') && (flag == 4)){
      throw ("wrong input! value need only one dot and numbers");
    }
  }
  this->map1[leftSide] = strtod(c,NULL);
}

Expression* Interpreter::interpret(string str) {
  for (unsigned long j = 0; j < str.size(); j++) {
    if (j == 0) {
      continue;
    } else {
      if (str[j] == ')') {
        if (str[j - 1] == '(') {
          throw ("wrong input! () without numbers ");
        }
      }
      if (str[j] == '(') {
        if (str[j - 1] == ')') {
          throw ("wrong input! )(   ");
        }
      }
      if ((str[j] == '+') || (str[j] == '-') || (str[j] == '*') || (str[j] == '/')) {
        if ((str[j - 1] == '+') || (str[j - 1] == '-') || (str[j - 1] == '*') || (str[j - 1] == '/')) {
          throw ("wrong input! more than one opertator close");
        }
      }
    }
  }
  for (map<string, double>::iterator it1 = map1.begin(); it1 != map1.end(); ++it1) {
    size_t pos = str.find(it1->first);
    while (pos != string::npos) {
      string ss = to_string(it1->second);
      str.replace(pos, it1->first.size(), ss);
      pos = it1->first.find(str, pos + ss.size());
    }
  }

  for (char c: str) {
    if (!((((c >= '0') && (c <= '9')) || (c == '.') || (c == '(') || (c == ')') || (c == '*') || (c == '/')
        || (c == '+') || (c == '-')))) {
      throw ("variable didnt exist in set");
    }
  }
  stack<char> stack_char;
  queue<string> que;
  unsigned long i = 0;
  int rightBracket = 0;
  int leftBracket = 0;
  for (char c : str) {
    if (c == '(') {
      leftBracket++;
    } else if (c == ')') {
      rightBracket++;
    } else {
      continue;
    }
  }
  if (rightBracket != leftBracket) {
    throw ("wrong input! bracket left and right not equal");
  }
  //running on the string
  while (i < str.length()) {
    if (str[i] == ' ') {
      i++;
      continue;
    }
    // case that the char is +
    if (str[i] == '+') {
      //-------------------------------maybe-------------------------
      if (!stack_char.empty()) {
        if (stack_char.top() == '$') {
          que.push("$");
          stack_char.pop();
        } else if (stack_char.top() == '&') {
          que.push("&");
          stack_char.pop();
        }
      }
      //--------------------------------------------------------------------------------add uplus--------------
      if (i == 0) {
        stack_char.push('&');
        stack_char.pop();
        i++;
        continue;
      }
      if (str[i - 1] == '(') {
        unsigned long j = i;
        while (j < str.size()) {
          if (str[j + 2] == ')') {
            que.push(str.substr(i + 1, j - i + 1));
            i = j + 1;
            break;
          } else if ((str[j + 2] == '+') || (str[j + 2] == '*') || (str[j + 2] == '-') || (str[j + 2] == '/')) {
            if (str[j + 1] != '(') {
              que.push(str.substr(i + 1, j - i + 1));
              i = j + 1;
              break;
            } else {
              break;
            }

          } else if (str[j + 2] == '(') {
            break;
          } else {
            j++;
          }
        }
        stack_char.push(('&'));
        i++;
        continue;
      }
      // div or mult inside the stack and we need to switch
      while (!stack_char.empty()) {
        if (stack_char.top() == '*') {
          que.push("*");
          stack_char.pop();
        } else if (stack_char.top() == '/') {
          que.push("/");
          stack_char.pop();
        } else {
          break;
        }
      }
      stack_char.push(str[i]);
      i++;
      //case that the char is -
    } else if (str[i] == '-') {
      //-------------------------------maybe-------------------------
      if (!stack_char.empty()) {
        if (stack_char.top() == '$') {
          que.push("$");
          stack_char.pop();
        } else if (stack_char.top() == '&') {
          que.push("&");
          stack_char.pop();
        }
      }
      //case uminus
      if (i == 0) {
        stack_char.push('$');
        i++;
        continue;
      } // uminus in the middle
      if (str[i - 1] == '(') {
        unsigned long j = i;
        while (j < str.size()) {
          if (str[j + 2] == ')') {

            que.push(str.substr(i + 1, j - i + 1));
            i = j + 1;
            break;
          } else if ((str[j + 2] == '+') || (str[j + 2] == '*') || (str[j + 2] == '-') || (str[j + 2] == '/')) {
            if (str[j + 1] != '(') {
              que.push(str.substr(i + 1, j - i + 1));
              i = j + 1;
              break;
            }
            break;
          } else if (str[j + 2] == '(') {
            break;
          } else if ((str[j + 1] == '(') && (str[j - 1] == '(')) {
            break;
          } else {
            j++;
          }
        }
        stack_char.push(('$'));
        i++;
        continue;
      }
      // div or mult inside the stack and we need to switch
      while (!stack_char.empty()) {
        if (stack_char.top() == '*') {
          que.push("*");
          stack_char.pop();
        } else if (stack_char.top() == '/') {
          que.push("/");
          stack_char.pop();
        } else {
          break;
        }
      }
      stack_char.push(str[i]);
      i++;
    } else if (str[i] == '/') {
      //--------------------------------maybe------------------------
      if (!stack_char.empty()) {
        if (stack_char.top() == '$') {
          que.push("$");
          stack_char.pop();
        } else if (stack_char.top() == '&') {
          que.push("&");
          stack_char.pop();
        }
      }
      stack_char.push(str[i]);
      i++;
    } else if (str[i] == '*') {
      //----------------------------maybe-----------------
      if (!stack_char.empty()) {
        if (stack_char.top() == '$') {
          que.push("$");
          stack_char.pop();
        } else if (stack_char.top() == '&') {
          que.push("&");
          stack_char.pop();
        }
      }
      stack_char.push(str[i]);
      i++;
    } else if (str[i] == '(') {
      stack_char.push(str[i]);
      i++;
    } else if (str[i] == ')') {
      if (i == 0) {
        throw ("wrong input! ) at the start of the line");
      }
      while ((!stack_char.empty()) && (stack_char.top() != '(')) {
        string s = string(1, stack_char.top());
        if (s != ")") {
          que.push(s);
        }
        stack_char.pop();
      }
      //delete the '('
      if (stack_char.empty()) {
        break;
      }
      if (stack_char.top() == '(') {
        stack_char.pop();
        i++;
        continue;
      }

      stack_char.push(str[i]);
      i++;
    } else { //not operator
      unsigned long j = i;
      while (j < str.length()) {
        if ((j + 1 == str.length()) || (str[j + 1] == '+') || (str[j + 1] == '-') || (str[j + 1] == '*')
            || (str[j + 1] == '/') || (str[j + 1] == '(') || (str[j + 1] == ')')) {
          que.push(str.substr(i, j - i + 1));
          i = j + 1;
          break;
        } else {
          j++;
        }
      }
    }
  }
  //end read the string

  while (!stack_char.empty()) {
    string s = string(1, stack_char.top());
    que.push(s);
    stack_char.pop();
  }

  stack<Expression *> expStack;
  while (!que.empty()) {
    Expression *exp1;
    Expression *exp2;
    string popue = que.front();
    if (popue == "$") {
      if (expStack.empty()) {
        que.pop();
        string ss1 = que.front();
        Expression *exp5 = new Value(stod(ss1));
        Expression *newUMin = new UMinus(exp5);
        expStack.push(newUMin);
        que.pop();
        continue;
      }
      exp1 = expStack.top();
      expStack.pop();
      Expression *newUMin = new UMinus(exp1);
      expStack.push(newUMin);
      que.pop();
      continue;
    }
    if (popue == "&") {
      if (expStack.empty()) {
        que.pop();
        string ss1 = que.front();
        Expression *exp5 = new Value(stod(ss1));
        Expression *newUPlus = new UPlus(exp5);
        expStack.push(newUPlus);
        que.pop();
        continue;
      }
      exp1 = expStack.top();
      expStack.pop();
      Expression *newUPlus = new UPlus(exp1);
      expStack.push(newUPlus);
      que.pop();
      continue;
    }
    if ((popue == "-") || (popue == "+") || (popue == "*") || (popue == "/")) {
      exp1 = expStack.top();
      expStack.pop();
      exp2 = expStack.top();
      expStack.pop();
      if (popue == "-") {
        Expression *newExpMin = new Minus(exp2, exp1);
        expStack.push(newExpMin);
        que.pop();
      } else if (popue == "+") {
        Expression *newExpPlus = new Plus(exp1, exp2);
        expStack.push(newExpPlus);
        que.pop();
      } else if (popue == "/") {
        Expression *newExpDiv = new Div(exp2, exp1);
        expStack.push(newExpDiv);
        que.pop();
      } else if (popue == "*") {
        Expression *newExpMul = new Mul(exp1, exp2);
        expStack.push(newExpMul);
        que.pop();
      }
    } else { // string is a number
      Expression *v = new Value(stod(popue));
      expStack.push(v);
      que.pop();
    }
  }
  return expStack.top();
}