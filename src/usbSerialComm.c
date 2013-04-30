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

/** Use following to help implement log files?
void usage(void);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until);
*/


 int g_fd = 0; //file descriptor of port

/**
 * Sets the user's Baud Rate.
 */
int setBaudRate(int baudNumber){
 
	int returnedNumber = 9600;
    return returnedNumber;
}


/**
 * Purpose: Sets up communication on port specified at baud rate specified if
 * possible and handles the details. It returns an integer where non-zero is
 * success meaning the connection was setup successfully.
 * @param portName String name of port to open (if COM10+ needs to be DOS name \\.\COM10 etc.)
 * @param portBaudRate Int for the baud rate of connection (serial) to the Arduino 9600 is standard.
 * @return int for success 0 is failed and 1 is success
 */
int setupCommunication(const char portName[], const int portBaudRate)
{ 
   int inPortBaudRate = 9600;
    
   g_fd = open(portName, O_RDWR); //port is port filename, /dev/ttyS0, /dev/tty01, etc.
   
   if (g_fd == -1) 
   {
     printf("\n*Error opening serial port %s at rate %i! Communication not established. \n\n", portName, portBaudRate);
    
     //return 1; //success
    }

} //end function to setup communication with Arduino


/**
 * Closes the active connection and frees up resources.
 * @return int 0 for failure and non-zero for success
 */
int closeCommunication(void)
{
     close(g_fd); //Close the connection
    
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
void sendToWheelChairController(const char toSend)
{

} //end sendIntToArduino function

/**
 * Delay function for program between serial communication.
 * @param integer time where time is in milliseconds
 */
void delayProgram(const int time)
{
	int timeToMilliSecs = (time * 1000); 
	//this converts the input (milliseconds to be same interface as windows) to the required microseconds by the unix cmd
	usleep(timeToMilliSecs);
}

//END file usbSerialCommNoWin.c 
