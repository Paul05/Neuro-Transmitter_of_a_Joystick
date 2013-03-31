/*
 * File:   forward.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
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
void goForward()
{
    sendToWheelChairController(extG_controllerForwardCmd);
    printf("You are going forward.\n");
    delayProgram(1000);

} //end goForward function

//END file forward.c
