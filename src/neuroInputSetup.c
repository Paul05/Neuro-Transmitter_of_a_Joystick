/*
 * File:   neuroInputSetup.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Allows the user to change the left/right/back/forward/exit keys.
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include "neuroInputSetup.h"
#include "userInput.h"
#include "usbSerialComm.h"

void changeMovementCommands()
{
    char userAnswer = 'z';
    printf("\n\nThe default inputs for the the Neuro-Headset and WheelChair Controller are: "
            "\n\n\tw for forward, s for backward, a for left, d for right, and x for "
            "exiting the program. \n\nDo you wish to change the defaults? "
            "\n\n\tType [Y] for yes or [N] for no: ");

    userAnswer = (char)getCharWithEnter();
   
    if( userAnswer == 'y' || userAnswer == 'Y' )
    {
        printf("\n\nUse the headset and perform the motion to go forward."
                "\n\tForward Cmd: ");
        extG_controllerForwardCmd = getCharWithEnter();
        printf("\n\nNow perform the command to go backwards. "
                "\n\tBackwards Cmd: ");
        extG_controllerBackCmd = getCharWithEnter();
        printf("\n\nNext, perform the command for left?"
                "\n\tLeft Cmd: ");
        extG_controllerLeftCmd = getCharWithEnter();
        printf("\n\nFinally, perform the command for right. "
                "\n\tRight Cmd: ");
        extG_controllerRightCmd = getCharWithEnter();
        printf("\n\nAdditionaly, press the key or perform the action to exit the program."
                "\n\tExit Cmd: ");
        extG_controllerExitCmd = getCharWithEnter();
        printf("\n\nFantastic! All of the keys have now been changed succesfully.\n");
    }
    else
    {
        printf("\nThe default input commands have stayed the same.\n\n");
    }    
    
} //end function changeMovementCommands

//END file neuroInputSetup.c
