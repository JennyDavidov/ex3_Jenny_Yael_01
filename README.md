# Jenny's and Yael's Project

## First Milestone : Interpreter

This project is our third exercise in the Algorithmic Programming 1 course. 
In this assignment we wrote an interpreter to code that handle a Unmanned aerial vehicle.
Our plane fly in the virtual space of the flight simulator – FlightGear.
FlightGear Flight Simulator is a free, open source multi-platform flight simulator developed by 
the FlightGear project since 1997. In our project it plays role of both server and client. 


### Prerequisites
The requirements that we should implements in this project were:
* Design patterns.
* Client server communication.
* Using data flows.
* Parallel computing using Threads.
* Working as team and dividing tasks between us.


### Running the tests
In order to run the proggram, meaning see the plane flying, you should provide fly.txt file.
This file should include commands, in the new programming language that the project interprets. 
After running the file, you will see in the console several messages that indicates the plane status,
from "let's fly" at the begining until "done" at the end of the fly.


### Process Description
At the begining of the project, we started planning our workplan. 
We defined detailed tasks and then divided them between us.
We started with the Lexer function - we devided every line in the fly.txt file into tokens.
Afther that we build the Parser Command - this command sends every string from the token array 
to the relevant command that can perform execute and apply the command.
We had several commands, so we use interface, that specify the behavior that the Commands classes should implement: 
execute method. Each command implements the relevant functionality.


### GitHub Link
https://github.com/JennyDavidov/ex3_Jenny_Yael_01




