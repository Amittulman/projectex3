//
// Created by amittulman on 17/12/2019.
//

#include "dataManager.h"
#include "openServerCommand.h"
#include "connectCommand.h"

using namespace std;

void dataManager::initializerMaps() {
  this->simMap.insert(std::pair<string,varData*>("instrumentation/airspeed-indicator/indicated-speed-kt",new varData("instrumentation/airspeed-indicator/indicated-speed-kt",0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/altimeter/indicated-altitude-ft", new varData("instrumentation/altimeter/indicated-altitude-ft" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/altimeter/pressure-alt-ft", new varData("instrumentation/altimeter/pressure-alt-ft" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/attitude-indicator/indicated-pitch-deg", new varData("instrumentation/attitude-indicator/indicated-pitch-deg" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/attitude-indicator/indicated-roll-deg", new varData("instrumentation/attitude-indicator/indicated-roll-deg" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/attitude-indicator/internal-pitch-deg", new varData("instrumentation/attitude-indicator/internal-pitch-deg" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/attitude-indicator/internal-roll-deg", new varData("instrumentation/attitude-indicator/internal-roll-deg" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/encoder/indicated-altitude-ft", new varData("instrumentation/encoder/indicated-altitude-ft" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/encoder/pressure-alt-ft", new varData("instrumentation/encoder/pressure-alt-ft" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/gps/indicated-altitude-ft", new varData("instrumentation/gps/indicated-altitude-ft" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/gps/indicated-ground-speed-kt", new varData("instrumentation/gps/indicated-ground-speed-kt" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/gps/indicated-vertical-speed", new varData("instrumentation/gps/indicated-vertical-speed" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/heading-indicator/indicated-heading-deg", new varData("instrumentation/heading-indicator/indicated-heading-deg" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/magnetic-compass/indicated-heading-deg", new varData("instrumentation/magnetic-compass/indicated-heading-deg" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/slip-skid-ball/indicated-slip-skid", new varData("instrumentation/slip-skid-ball/indicated-slip-skid" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/turn-indicator/indicated-turn-rate", new varData("instrumentation/turn-indicator/indicated-turn-rate" ,0)));
  this->simMap.insert(std::pair<string,varData*>("instrumentation/vertical-speed-indicator/indicated-speed-fpm", new varData("instrumentation/vertical-speed-indicator/indicated-speed-fpm" ,0)));
  this->simMap.insert(std::pair<string,varData*>("controls/flight/aileron" , new varData("controls/flight/aileron" ,0)));
  this->simMap.insert(std::pair<string,varData*>("controls/flight/elevator", new varData("controls/flight/elevator" ,0)));
  this->simMap.insert(std::pair<string,varData*>("controls/flight/rudder", new varData("controls/flight/rudder" ,0)));
  this->simMap.insert(std::pair<string,varData*>("controls/flight/flaps", new varData("controls/flight/flaps" ,0)));
  this->simMap.insert(std::pair<string,varData*>("controls/engines/current-engine/throttle", new varData("controls/engines/current-engine/throttle" ,0)));
  this->simMap.insert(std::pair<string,varData*>("engines/engine/rpm", new varData("engines/engine/rpm" ,0)));

  //initialize map of commands
  commandsMap.insert(pair<string,Command*>("openDataServer",new openServerCommand()));
  commandsMap.insert(pair<string,Command*>("connectControlClient",new connectCommand()));
/*  commandsMap.insert(pair<string,Command*>("var",new defineVarCommand()));
  commandsMap.insert(pair<string,Command*>("while",new whileCommand()));
  commandsMap.insert(pair<string,Command*>("if",new ifCommand()));
  commandsMap.insert(pair<string,Command*>("print",new printCommand()));
  commandsMap.insert(pair<string,Command*>("sleep",new sleepCommand()));*/
}
dataManager* dataManager::dataInstance = 0;