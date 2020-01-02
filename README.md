# About
This project is the first part of final project for Advanced Programming course in CS-BIU, by Guy Stepanenko and Amit Tulman.
The project is written in C++.
https://github.com/Amittulman/projectex3

# FlightSimulator
This project simulates an auto pilot for FightGear simulator, which means receiving a txt file with human readable commands, and making a Cessna 172 fly.
In order for this to happen, we lexed the text file, parsed it and executed each of the commands in a way that FightGear simulator can understand, while receiving airplane's data and running the commands according to it's condition.
The communication with the simulator works through TCP networking.

## Installation

In order to use the code, you will need:

[FlightGear](https://www.flightgear.org/) simulator to be installed.

After the installation, go to settings and add these lines to "Additional Settings":
```bash
--telnet=socket,in,10,10.0.2,5402,tcp --httpd=8080
generic=socket,out,10,127.0.1,5400,tcp,generic_small --
```
Add "generic_small.xml" file to the simulator installation path.
## Usage
Linux:
Compile the code using the following command:
```bash
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
Run the .out file with flight instructions text file's path as an argument to main.
Run the simulator, click "fly", and enjoy the view :)
