/*
* File: right.c
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

void goRight()
{
    sendToWheelChairController(extG_controllerRightCmd);
    printf("You are going right.\n");
    delayProgram(1000);

} //end goRight function

//END file right.c
