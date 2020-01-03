# Jenny's and Yael's Project

## First Milestone : Interpreter

This project is our third exercise in the Algorithmic Programming 1 course. 
In this assignment we wrote an interpreter to code that handle a Unmanned aerial vehicle.
Our plane fly in the virtual space of the flight simulator – FlightGear.
FlightGear Flight Simulator is a free, open source multi-platform flight simulator developed by 
the FlightGear project since 1997. In our project it plays role of both server and client. 
FlightGear installation done by following the instructions in the website: https://www.flightgear.org/download/main-program/.
It explicitly says how to download on which OS and where the files exist once you download onto your machine.
If you're using Ubuntu, you can install flightgear from the app store (software center) that ubuntu has.


### Prerequisites
The requirements that we should implements in this project were:
* Design patterns.
* Client server communication.
* Using data flows.
* Parallel computing using Threads.
* Working as team and dividing tasks between us.


### Running the tests
In order to run the proggram, meaning see the plane flying, you should provide fly.txt file and generic_small_xml files.
This file should include commands, in the new programming language that the project interprets. 
In order to run the program, you should follow the following instructions:
*  The simulator needs to have the following settings written before it launches:
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small   
--telnet=socket,in,10,127.0.0.1,5402,tcp
*  Compile with the command:
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
After running the file, you will see in the console several messages that indicates the plane status. 
In the begining, we will recieve a messge that the server is listening and then we can press the fly! bottun.
After the connection with the client succedded as well, we will recieve a message that we need to wait two minutes so the gui screen could be loaded.
After that, we will get a "let's fly" message, and the plane will fly until the "done" message at the end of the fly.
The generic_small.xml file,provides the type of information the simulator sends.
When the sumulator will send data, it will be separated by commas, in the same order as they appear in the generic_small.xml.
The file “generic_small.xml” needs to be in the protocol folder under data of the simulator code (wherever you downloaded it to), and the fly.txt file should be in the project folder, in parallel to the main.



### Process Description
At the begining of the project, we started planning our workplan. 
We defined detailed tasks and then divided them between us.
We started with the Lexer function - we devided every line in the fly.txt file into tokens.
After that we build the Parser Command - this command sends every string from the token array 
to the relevant command that can perform execute and apply the command.
We had several commands, so we use interface, that specify the behavior that the Commands classes should implement: 
execute method. Each command implements the relevant functionality.


### GitHub Link
https://github.com/JennyDavidov/ex3_Jenny_Yael_01




