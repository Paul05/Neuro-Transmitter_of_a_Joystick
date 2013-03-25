Neuro-Transmitter_of_a_Joystick Project
=======================================
Franklin Liu, Darryl Monroe, Michael Berg, Paul Spaude
CST315 - CST316  ASU Polytechnic All Rights Reserved. 

**Description**
This software is part of a larger project that involves
modifications to an electric wheelchair and use of an 
EEG or other input device to control a wheelchair. 
This software is a C console based application that is
designed to normalize input and provide easier more intuitive 
control of the wheelchair than existing Neuro-headsets and 
software alone supply.

This application is designed to work with the propietary or other 
neuro-device software in form of keyboard inputs. 
This means that the neuro headset's software must output at least 2 
actions in the form of keystrokes and can have up to four 
(for the four directions). Furthermore, the software must designate 
this application as the intended recipient. Typical mappings are: 
W for forward, S for backward, A for left, and D for right.
Certain directions may be limited by the hardware, but that is also up to the 
user to specify with the Arduino. 

This program outputs commands to an Arduino acting as a slave controller 
connected to an electric wheelchair. It is assumed the Arduino is connected 
via USB or serial port and that the port name and baud rate is known. 
Typically, even if connected via USB the Arduino mimics a serial port. 
The name will be aliased to something like COM1 for example. The baud rate
will be specified in the Arduino setup and code itself. The Arduino should
furthermore be setup to recieve chars or "strings" from the serial connection.
Currently, this program is setup for W for forward, S for backward, A for left, 
and D for right. T should be reserved for testing, and x should not be used as that 
is an exit command. 

**Instructions on How To Build and Execute this Application**
This application can be executed on Windows or Linux/Unix and the included build.xml file takes care
of certain operating system issues. To build the software type 'ant build' in the directory 
where this software is located and the build.xml is located. You should get a message
that it completed successfully. You do need the cpptasks.jar in the ant/lib directory (included in
the lib directory of this repository). You also need a C compiler (and of course Ant) on your path 
in your shell(Linux/Unix) or system environment path(Windows). If using Windows
the compiler(s) can be from mingw or cygwin as it has been tested with the gcc compiler collection. 

To run or execute the program navigate to the dist directory after it has built successfully. There there will
be only one executable there: "NeuroControlProgram". Run that file and that is it! At any time in the program you
can exit by typing "exit" or "x" if in the neuro-control portion of the program.

**Other Options Available with Ant**
There are other options available in build.xml. To see all options available type "ant targets"
in the command or shell prompt. These can be run by typing "ant target" where target is changed
to the target name you wish to execute.

The targets restoreWin and restoreUnix revert changes made when built on a particular system. 
You should only need to run this if you wish to keep the original github structure intact, 
otherwise the changes are designed for your system and shouldn't need to be changed. 

To static test the code typing 'ant static_test' will test the code with cppcheck a static test tool that 
aims to find things the compiler wouldn't have found. (Thus it doesn't duplicate the compiler warnings and errors). 
By typing 'ant static_test' and having cppcheck/bin on the path, it should run the test, and then put the results 
in errorsStaticCheck.xml file under tests directory. 

**THIS SECTION SUBJECT TO CHANGE AND THERE WILL BE MORE TOOLS ADDED SOON**

Thanks for reading and hope you find this software useful! 

**END README**
