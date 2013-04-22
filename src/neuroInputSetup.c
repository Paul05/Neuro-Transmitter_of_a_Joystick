/*
 * File:   neuroInputSetup.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Allows the user to change the movement keys. There is a contract
 *          between the WheelChair Controller and the Neuro-Headset
 *          that the inputs will be the same between the two devices. So, any
 *          changes here by a user would need to be altered in the controller
 *          setup as well.
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include "neuroInputSetup.h"
#include "userInput.h"
#include "usbSerialComm.h"

void changeMovementCommands(void)
{
    char userAnswer = 'z';

    printf("\n\n\n\nThe default inputs for the the Neuro-Headset and WheelChair Controller are: "
            "\n\n\tw for forward, s for backward, a for left, d for right, and x for "
            "exiting the program. \n\nDo you wish to change the defaults? "
            "\n\n\tWarning: Any changes here will have to be applied to the wheelchair controller as well!"
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
