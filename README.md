Neuro-Transmitter_of_a_Joystick
===============================
Franklin Liu, Darryl Monroe, Michael Berg, Paul Spaude
CST315 - CST316  ASU Polytechnic All Rights Reserved. 

This program handles communication between a Emotiv Epoc headset
and an Arduino Mega. It is assumed the Arduino is connected via USB
and that a serial port is being mimicked (default arduino behavior).

The Arduino Mega should furthermore be setup to connect to a wheelchair
and act as a slave controller to this program and the computer it runs on.
It should take an input of a char and move the wheelchair in the indicated direction 
and do nothing otherwise. 

This program can be built on Windows or Linux/Unix but currently due to limitations of
hardware/software it can only be run on Windows. The included build.xml file takes care
of certain linux/unix dependencies so that it can be built for automated server build 
environments. 

To build type 'ant build' in the directory where build.xml is located. You should get a message
that it completed successfully. You do need the cpptasks.jar in the ant/lib directory. You also
need the gcc/g++ compilers in your path, this can be from mingw or cygwin (if on Windows). 
Furthermore, you will need cppcheck/bin on your path if you want to static test the code.

If you are on Windows you can navigate to the dist directory
and find the .exe file and run it. The program runs on the console and gives instructions. You can 
exit at any time by typing exit or an x depending. The program takes initial input on the command line 
or from the keyboard (with the keyboard being preferred) and will validate the input as best as possible.
It also takes input from the keyboard, from the emotiv device (emokey). 

Other build possibilities are: clean, restoreWin, restoreUnix and static_test. 
restoreWin and restoreUnix revert changes made when built on a particular system. You only need to run this 
if you wish to keep the original virgin github structure intact, otherwise the changes are designed for your
system and shouldn't need to be reverted. 

static_test will test the code with cppcheck a static test tool that 
aims to find things the compiler wouldn't have found. (Thus it doesn't duplicate the compiler warnings and errors). 
By typing 'ant static_test' and having cppcheck/bin on the path, it should run the test, and then put the results 
in errorsStaticCheck.xml file under src directory. 