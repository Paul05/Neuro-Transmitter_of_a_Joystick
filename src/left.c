/*
* File: left.c
* Author: Neuro-Transmitter Group
* Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
* Class: CST315 & CST316 ASU Polytechnic
*
* Purpose:
*
* Created Spring, 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include "usbSerialComm.h"

/**
 * 
 */
 void goLeft()
 {
     sendToWheelChairController(extG_controllerLeftCmd);    
     delayProgram(400);

 }//end goLeft function

//END file left.c
