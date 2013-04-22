/*
 * File:   userOutput.h
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This file contains functions that output data or prompts to the user.
 *
 *  * Created Spring, 2013
 */

#ifndef USEROUTPUT_H
#define	USEROUTPUT_H

void welcomeMessage(void);
void exitMessage(void);
void showUserInstructionMessage(void);
void showMenu(void);
void showSetupConfiguration(int baudRate, const char portName[]);

#endif	/* USEROUTPUT_H */

//END file userOutput.h/
