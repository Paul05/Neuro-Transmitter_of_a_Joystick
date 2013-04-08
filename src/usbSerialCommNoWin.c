/*
 * File:   usbSerialCommNoWin.c  
 *
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Contains functions to communicate with a serial port
 *          which is intended to be an arduino connected via USB.
 *  
 * Note: This is platform specific to UNIX/Linux.
 *
 * Created Spring, 2013
 */

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "usbSerialComm.h"


char extG_controllerTestCmd = 't';
char extG_controllerForwardCmd = 'w';
char extG_controllerBackCmd = 's';
char extG_controllerRightCmd = 'd';
char extG_controllerLeftCmd = 'a';
char extG_controllerExitCmd = 'x';
char g_last_userInput[3];


/**
 * Purpose: Sets up communication on port specified at baud rate specified if
 * possible and handles the details. It returns an integer where non-zero is
 * success meaning the connection was setup successfully.
 * @param portName String name of port to open (if COM10+ needs to be DOS name \\.\COM10 etc.)
 * @param portBaudRate Int for the baud rate of connection (serial) to the Arduino 9600 is standard.
 * @return int for success 0 is failed and 1 is success
 */
int setupCommunication(const char inPortName[], const int inPortBaudRate)
{ 
         return 1; //success

} //end function to setup communication with Arduino


/**
 * Closes the active connection and frees up resources.
 * @return int 0 for failure and non-zero for success
 */
int closeCommunication(void)
{
    return 1;
    
} //end closeCommunication function


/**
 * Tests the connection (send and recieve) from the Arduino device
 * connected on the currently open connection.
 * @return  int 0 for failure and non-zero for success
 */
int testControllerCommunication(void)
{
      return 1;
} //end testCommunication function 


/**
 * Tests the operation of the device by sending brief 
 * movement commands.
 */
 void testWheelChairOperation(void)
 {
 
 } //end testOperation function

 
/**
 * Sends an integer to the currently open device.
 * @param toSend integer to send to Arduino
 */
void sendToWheelChairController(char toSend)
{

} //end sendIntToArduino function

/**
 * Delay function for program between serial communication.
 * @param integer time where time is in milliseconds
 */
void delayProgram(int time)
{
	int timeToMilliSecs = (time * 1000); 
	//this converts the input (milliseconds to be same interface as windows) to the required microseconds by the unix cmd
	usleep(timeToMilliSecs);
}

//END file usbSerialCommNoWin.c 
