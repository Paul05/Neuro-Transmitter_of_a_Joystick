Neuro-Transmitter_of_a_Joystick
===============================
Franklin Liu, Darryl Monroe, Michael Berg, Paul Spaude
CST315 - CST316  ASU Polytechnic All Rights Reserved. 

This program handles communication between a Emotiv Epoc headset
EmoKey Software and an Arduino Mega acting as a slave controller 
connected to a wheelchiar. It is assumed the Arduino is connected via USB
and that a serial port is being mimicked (default arduino behavior).

The Arduino Mega should furthermore be able to recieve input from the serial
connection and be setup to move a joystick or the wheelchair in directions.
It should take an input of a char and move the wheelchair in the indicated direction 
and do nothing otherwise. 

**SUBJECT TO CHANGE SHORTLY**
This program can be built on Windows or Linux/Unix but currently due to limitations of
hardware/software it can only be fully ran on Windows. The included build.xml file takes care
of certain linux/unix dependencies so that it can be built for automated server build 
environments. 
**

To build type 'ant build' in the directory where build.xml is located. You should get a message
that it completed successfully. You do need the cpptasks.jar in the ant/lib directory. You also
need the gcc/g++ compilers in your path, this can be from mingw or cygwin (if on Windows). 
Furthermore, you will need cppcheck/bin on your path if you want to static test the code.
**SUBJECT TO CHANGE ADD MORE TOOLS**

To run or execute the program navigate to the dist directory
and find the .exe file and run it. 
The program runs on the console and gives instructions. You can exit at any time by typing exit or an x depending. 
The program takes initial input on the command line or from the keyboard (with the keyboard being preferred) 
and will validate the input as best as possible.
It also takes input from the "keyboard", from the emotiv device (Emokey) without enter needing to be pressed.
You should know the serial port name the Arduino is connected to (COM1 for example) and the baud rate (in Arduino
setup). Default baud rate is typically 9600, although we support all that are available in the Windows.h libarary. 

Other sometimes necessary targets are: clean, restoreWin, and restoreUnix. 
restoreWin and restoreUnix revert changes made when built on a particular system. You only need to run this 
if you wish to keep the original virgin github structure intact, otherwise the changes are designed for your
system and shouldn't need to be reverted. 

To static test the code typing 'ant static_test' will test the code with cppcheck a static test tool that 
aims to find things the compiler wouldn't have found. (Thus it doesn't duplicate the compiler warnings and errors). 
By typing 'ant static_test' and having cppcheck/bin on the path, it should run the test, and then put the results 
in errorsStaticCheck.xml file under src directory. 