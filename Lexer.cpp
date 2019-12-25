//
// Created by amittulman on 16/12/2019.
//

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Lexer.h"

using namespace std;

vector<string> Lexer::split(string s){
  vector<string> lexedVector;

  string commandsLine;
  ifstream myfile;
  myfile.open(s);

  if (!myfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }
  while (getline(myfile, commandsLine)) {
    while (commandsLine[0] == '\t') {
      commandsLine = commandsLine.substr(1,commandsLine.length() - 1);
    }
    //commandsLine.erase(std::remove(commandsLine.begin(), commandsLine.end(), '\t'), commandsLine.end());
    while (commandsLine[0] == ' ') {
      commandsLine = commandsLine.substr(1,commandsLine.length() - 1);
    }

    size_t prevPos = 0, position, position2;
    if (position = commandsLine.find("while ") != string::npos) {
      position = commandsLine.find("while ");
      lexedVector.push_back("while");
      position = commandsLine.find("{");
      lexedVector.push_back(commandsLine.substr(6, commandsLine.length() - 8)); // After while before {
      lexedVector.push_back("{");
    }
    else if (position = commandsLine.find("if ") != string::npos) {
      position = commandsLine.find("if ");
      lexedVector.push_back("if");
      position = commandsLine.find("{");
      lexedVector.push_back(commandsLine.substr(3, position - 4)); // After while before {
      lexedVector.push_back("{");
    }
    else if (position = commandsLine.find("sim(\"") != string::npos) {
      position = commandsLine.find("sim(\"");
      lexedVector.push_back("var");
      lexedVector.push_back(commandsLine.substr(4, (position - 8))); // After var  arrow
      lexedVector.push_back(commandsLine.substr(position - 3, 2)); // the arrow
      lexedVector.push_back("sim");
      lexedVector.push_back(commandsLine.substr(position + 4, commandsLine.length() - position - 5));

    }
    else if (position = commandsLine.find("{") != string::npos){
      lexedVector.push_back("$func");
      position = commandsLine.find("{");
      int positionOpen = commandsLine.find("(");
      lexedVector.push_back(commandsLine.substr(0, positionOpen)); //Name of the function
      lexedVector.push_back(commandsLine.substr(positionOpen+1, position-positionOpen-2)); //Name of the function
      lexedVector.push_back("{");


    }
    else if (position = commandsLine.find("=") != string::npos) { // Case rudder = -1 or var h0 = 8
      position = commandsLine.find("=");
      if ((position2 = commandsLine.find("var ") != string::npos)) {
        if (position2 == 1) {
          lexedVector.push_back("var");
          if(commandsLine[position -1] != ' ') //If there are no spaces before the "="
            lexedVector.push_back(commandsLine.substr(4, position - 6)); // if "var" is in line
          else
            lexedVector.push_back(commandsLine.substr(4, position - 5)); // if "var" is in line
        }
      }// rudder = 0
      else {
        if(commandsLine[position -1] != ' ') //If there are no spaces before the "="
          lexedVector.push_back(commandsLine.substr(0, position)); //  if "var" is in NOT line
        else
          lexedVector.push_back(commandsLine.substr(0, position - 1)); //  if "var" is in NOT line
      }
      lexedVector.push_back("=");
      if(commandsLine[position + 1] != ' ') //If there are no spaces after the "="
        lexedVector.push_back(commandsLine.substr(position + 1, commandsLine.length() - position - 3)); // After =
      else
        lexedVector.push_back(commandsLine.substr(position + 2, commandsLine.length() - position - 2)); // After =
    }
    else if (position = commandsLine.find("connectControlClient") != string::npos) {
      position = commandsLine.find("connectControlClient");
      lexedVector.push_back("connectControlClient");
      position2 = commandsLine.find(',');
      lexedVector.push_back(commandsLine.substr(21, position2 - 21)); // IP
      lexedVector.push_back(commandsLine.substr(position2 + 1, commandsLine.length() - position2 - 2)); //Port
    }
    else if (position = commandsLine.find('(') != string::npos) {
      position = commandsLine.find('(');
      lexedVector.push_back(commandsLine.substr(0, position)); //Command
      int len = commandsLine.length();
      lexedVector.push_back(commandsLine.substr(position + 1, (len - position - 2))); // the expression
    }
    else if (position = commandsLine.find('}') != string::npos) {
      lexedVector.push_back("}");
    }
  }
  return lexedVector;
}
