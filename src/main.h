/*
* File: main.h
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*        Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Input: The program will show a menu so that users can select different
*        options. All user information is inputted and communicated through
*        the console.
*
* Function: This program sets up communication with a wheelchair controller. The
*           connection may be USB or serial but the USB must mimic a serial port
*           and communication.
*           If the connection is setup successfully, this program will then
*           take inputs from the keyboard.
*           Default inputs are: t is reserved for testing and x is reserved
*           for exiting.
*           w is forward, s is back, d is right, and a is left.
*           Those last movement inputs are designed to be inputted from a "Neuro"
*           EEG/EMG headset. They may do this via their proprietary and/or
*           other open software. The goal is to map an action on the headset to
*           a designated keyboard character.
*           This program then sends that input to the wheelchair controller
*           after it normalizes the input to provide a consistent and usable
*           user experience. This version is in its infancy and is based on the
*           the Emotiv EPOC headset and its nuances.
*
* Created: Spring, 2013
*
*/

#ifndef MAIN_H
#define	MAIN_H

void portAndBaudCheck(const int baud, const char port[]);
void wheelChairControlLoop(void);
int performMenuAction(char actionNumberFromUser, int* p_baudRate, char portName[]);
void dynamicTestFunction(void);

#endif	/* MAIN_H */

//End of main.h
