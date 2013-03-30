/*
 * File:   backward.c
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
void goBackward()
{
    sendToWheelChairController(extG_controllerBackCmd);
    printf("You are going backwards.\n");
    delayProgram(1000);

} //end goBackward function

//END file backward.c
