//
// Created by amittulman on 06/11/2019.
//

#ifndef MOR1__EX1_H_
#define MOR1__EX1_H_
#include <string>
#include "Expression.h"
#include <map>
#include <deque>
#include <queue>

class Variable : public Expression {
 private:
  string name;
  double num;
 public:
  Variable(string s, double d) {
    this->name = s;
    this->num = d;
  }
  double calculate() override;
  Variable& operator++();
  Variable& operator--();
  Variable& operator+=(double);
  Variable& operator-=(double);
  Variable& operator++(int);
  Variable& operator--(int);
};

class UnaryOperator : public Expression {
 protected:
  Expression* expr1;
 public:
  UnaryOperator(Expression* exp) {
    this->expr1 = exp;
  }
  ~UnaryOperator() {
    delete expr1;
  }
};

class Value : public Expression {
 private:
  double val;
 public:
  Value(double d) {
    this->val = d;
  }
  double calculate() override;
};

class BinaryOperator : public Expression {
 protected:
  Expression* rightExp;
  Expression* leftExp;
 public:
  BinaryOperator(Expression* leftExp1, Expression* rightExp1) {
    this->rightExp = rightExp1;
    this->leftExp = leftExp1;
  }
  ~BinaryOperator() {
    if(this->rightExp != NULL) {
      delete this->rightExp;
    }
    if (this->leftExp != NULL) {
      delete this->leftExp;
    }
  }
};

class Plus : public BinaryOperator {
 public:
  Plus(Expression *leftExp12, Expression *rightEx12) : BinaryOperator(leftExp12,rightEx12){}
  double calculate() override;
};

class Minus : public BinaryOperator {
 public:
  Minus(Expression *leftExp11, Expression *rightEx11) : BinaryOperator(leftExp11, rightEx11){}
  double calculate() override;
};

class Mul : public BinaryOperator {
 public:
  Mul(Expression *leftExp2, Expression *rightEx2) : BinaryOperator(leftExp2, rightEx2){}
  double calculate() override;
};

class Div : public BinaryOperator {
 public:
  Div(Expression *leftExp1, Expression *rightEx1) : BinaryOperator(leftExp1, rightEx1){
    if (rightEx1->calculate() == 0) {
      throw ("error! divide by 0");
    }
  }
  double calculate() override;
};

class UPlus : public UnaryOperator {
 public:
  UPlus(Expression *expr) : UnaryOperator(expr){}
  double calculate() override;
};

class UMinus : public UnaryOperator {
 public:
  double calculate() override;
 public:
  UMinus(Expression *ex1) : UnaryOperator(ex1){}
};

class Interpreter {
 private:
  map<string, double> map1;
 public:
  void setVariables(string str);
  Expression* interpret(string str);
};
#endif //MOR1__EX1_H_