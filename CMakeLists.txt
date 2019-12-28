cmake_minimum_required(VERSION 3.15)
project(ex3_Test_Proj)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3_Test_Proj main.cpp OpenDataServerCommand.cpp ConnectControlClientCommand.cpp ConnectControlClientCommand.h Command.h OpenDataServerCommand.h Sim.cpp Sim.h Sleep.cpp Sleep.h Print.cpp Print.h xml.cpp xml.h interpreter.cpp interpreter.h Expression.h ex1.cpp ex1.h Assignment.cpp Assignment.h WhileCommand.cpp WhileCommand.h IfCommand.cpp IfCommand.h)