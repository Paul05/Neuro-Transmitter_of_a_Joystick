Neuro-Transmitter_of_a_Joystick Project
=======================================
Franklin Liu, Darryl Monroe, Michael Berg, Paul Spaude
CST315 - CST316  ASU Polytechnic All Rights Reserved. 

**Description**
This software is part of a larger project that involves
modifications to an electric wheelchair and use of an 
EEG or other input device to control a wheelchair. 
The program is a C console based application that is
designed to normalize input and provide easier more intuitive 
control of the wheelchair, than existing Neuro-headsets and 
software alone supply.

This application is designed to work with the propietary or other 
neuro-device software in form of keyboard inputs. 
This means that the neuro headset's software must output at least 2 
actions in the form of keystrokes and can have up to four 
(for the four directions). Furthermore, the software must designate 
this application as the intended recipient. Typical mappings are: 
W for forward, S for backward, A for left, and D for right.
Certain directions may be limited by the hardware, but that is also up to the 
user to specify with the wheelchair controller. 

This program outputs commands to a slave controller 
connected to the electric wheelchair. This controller can control
the joystick, a device to control the joystick, relays for for the
motor controller(s) itself, and more. 
However, it is assumed that the controller is connected via USB or serial port 
and that the port name and baud rate is known. 
Typically, even if connected via USB, many modern controllers mimic a serial port. 
The serial port name will be aliased to something such as COM1 on Windows for example.
It is Operating System specific and can vary between disconnections. The port can typically
be found in your Operating System specific setup for devices and hardware.  
The baud rate will be specified in the controller setup and code itself. 
The controller should also be setup to recieve strings from the serial connection and
output the string recently recieved when the test command is sent.
Currently, the program's defaults are w for forward, s for backward, a for left, 
and d for right. t should be reserved for testing, and x should not be used as that 
is an exit command. 
Sample code for the external controller is provided in the arduino folder. It was designed
for and tested on an Arduino Mega, but may work on other devices. 


**Instructions on How To Build and Execute this Application**
This application can be executed on Windows or Linux/Unix and Mac. The included build.xml file 
takes care of certain operating system issues. To build the software type 'ant build' in the 
directory where this software is located and the build.xml is located. You should get a message
that it completed successfully. You do need the cpptasks.jar in the ant/lib directory on your system. 
That jar file is included in the lib directory of this repository. 
You also need a C compiler (and of course Ant) on your path in your shell(Linux/Unix) or system environment path(Windows). 
If using Windows the compiler(s) can be from mingw or cygwin as it has been tested with the gcc compiler collection. 

To run or execute the program navigate to the dist directory after it has been built successfully. There will
be only one executable in the dist directory: "NeuroControlProgram". 
Run that executable and that is it! You should see a menu with several options!
At any time in the program you can exit to the menu by typing "exit" and it is changed to "x" 
if you are in the neuro-control portion of the program.
*Note: at this time the program will not communicate with the external controller under Linux, 
	Unix, or Mac operating systems. This is a future possibility, and most of the framework is there.*

**Other Options Available with Ant**
There are other options available in build.xml. To see all options available type "ant targets"
in the command or shell prompt. These can be run by typing "ant target" where target is changed
to the target name you wish to execute. Some may not be available on all Operating Systems and
most are there for development and debugging purposes. 

The targets restoreWin and restoreUnix revert changes made when built on a particular system. 
You should only need to run this if you wish to keep the original github structure intact, 
otherwise the changes are designed for your system and shouldn't need to be changed. 

Thanks for reading and hope you find this software useful! 

**END README**
