cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(ex3
        Command.h
        connectCommand.cpp
        connectCommand.h
        dataManager.cpp
        dataManager.h
        defineVarCommand.cpp
        defineVarCommand.h
        ex1.cpp
        ex1.h
        Expression.cpp
        Expression.h
        funcCommand.cpp
        funcCommand.h
        ifCommand.cpp
        ifCommand.h
        Lexer.cpp
        Lexer.h
        main.cpp
        openServerCommand.cpp
        openServerCommand.h
        Parser.cpp
        Parser.h
        printCommand.cpp
        printCommand.h
        sleepCommand.cpp
        sleepCommand.h
        varData.cpp
        varData.h
        whileCommand.cpp
        whileCommand.h)
