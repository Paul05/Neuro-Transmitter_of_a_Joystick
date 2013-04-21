/*
 * File:   userInput.h
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This file contains functions to get user input from the console.
 *  The functions in order: get a string port name, an integer baud rate, as
 *  well as a character, all from the console. The port name and baud rate
 *  handle limited error checking and limited bound checking for those inputs
 *  with constants defined in usbSerialComm.h. 
 *
 * Created Spring, 2013
 */

#ifndef USERINPUT_H

 #ifndef BUFFERLENGTH
    #define BUFFERLENGTH 128    //arbitrary size picked as standar input buffer length
 #endif
 #ifndef USEREXITCOMMAND
    #define USEREXITCOMMAND "exit"   //string the user is to type to exit out of input loops/program
 #endif

#define	USERINPUT_H

int getPortName(char outPortName[]);
int getBaudRate(void);
char getCharNoEnter(void);
char getCharWithEnter(void);

#endif	/* USERINPUT_H */

//END file userInput.h/


