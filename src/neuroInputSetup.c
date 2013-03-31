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
#include <ctype.h>
#include "neuroInputSetup.h"
#include "userInput.h"
#include "usbSerialComm.h"

void changeMovementCommands()
{
    char defaultChange = 'z';
    printf("The default inputs are W for forward, A for backward, S for left, D for right, and X for exiting the program while moving the wheelchair. Do you wish to change the defaults? Type [Y] for yes or [N] for no.\n");

    defaultChange = getCharConsole();
    defaultChange = tolower(defaultChange);

    if(defaultChange == 'y'){
        printf("Do the motion to go forward and that will be the new forward key\n");
        extG_controllerForwardCmd = tolower(getCharConsole());
        printf("Now the command to go backwards in the wheelchair. \n");
        extG_controllerBackCmd = tolower(getCharConsole());
        printf("Fantastic, halfway done. What would be the key command for left?\n");
        extG_controllerLeftCmd = tolower(getCharConsole());
        printf("And last but not least the command to go right. \n");
        extG_controllerRightCmd = tolower(getCharConsole());
        printf("Also, what is the new key to exit the program?\n");
        extG_controllerExitCmd = tolower(getCharConsole());
        printf("Fantastic! All of the keys have now been changed succesfully.\n");
    }else{
        printf("All right, the defaults for forward, back, left, right, and exit have stayed the same.\n\n");
    }    
    
} //end function changeMovementCommands

//END file neuroInputSetup.c
