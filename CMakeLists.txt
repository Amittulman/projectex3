cmake_minimum_required(VERSION 3.15)
project(projectex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(projectex3 Lexer.cpp Lexer.h Command.h Parser.cpp Parser.h openServerCommand.cpp openServerCommand.h connectCommand.cpp connectCommand.h server.cpp server.h client.cpp client.h dataManager.cpp dataManager.h varData.cpp varData.h main.cpp main.h)