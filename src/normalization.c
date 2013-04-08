/*
* File: normalization.c
* Author: Neuro-Transmitter Group
* Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
* Class: CST315 & CST316 ASU Polytechnic
*
* Purpose: Handles the normalization for input from a Neuro-Headset.
*           The current version represents the Emotiv Epoc Headset and
*           the intricacies of their proprietary algorithm and the limitations
*           of that headset. Although, it does generally deal with the problem
*           of measuring eye movement and other facial movements with an EEG/EMG
*           device in general.
*
* Created Spring, 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "normalization.h"
#include "usbSerialComm.h"
#include "left.h"
#include "right.h"
#include "forward.h"
#include "backward.h"

int g_count = 0;
char g_last_userInpt[3];

/*
 * This function hands off functionality to the appropriate normalization/direction
 * functions based on an inputted char.
 * @param char key
 */
void callNormalizeDirectionFuncs(char key)
{
     
    if ( key == extG_controllerForwardCmd )
    {
        goForward();
    }
    else if ( key == extG_controllerBackCmd )
    {
        goBackward();
    }
    else if ( key == extG_controllerLeftCmd )
    {
        goLeft();
    }
    else if ( key == extG_controllerRightCmd )
    {
        goRight();
    }
    else if ( key == extG_controllerTestCmd )
    {
        testControllerCommunication();
    }
    else if ( key == extG_controllerExitCmd )
    {
        printf("*Exit char recieved %c. \n\n", extG_controllerExitCmd);       
    }
    else
    {
         printf("\n*Error char not recognized! Char input: %c. \n\n", key); //char not recognized print error, will keep going though
    }//end switch on key

} //end callNormalizeDirectionFuncs function

void normalizationAlgorithm(){
    if(g_count == 0){
        g_last_userInpt[0] = toSend;
    }else if(g_count == 1){
        g_last_userInpt[1] = toSend;
    }else if(g_count == 2){
        g_last_userInpt[2] = toSend;
    }
    if(g_last_userInpt[0] == g_last_userInpt[1] && g_last_userInpt[0] == g_last_userInpt[2]){
        g_count = 0;
        char tempToSend[] = {toSend};
        WriteFile(g_controlDevice,tempToSend,strlen(tempToSend),&g_btsIO,NULL); //writes char to arduino
        ++g_count;
    }else if(!isnan(g_last_userInpt[2])){
        if(g_last_userInpt[0] == g_last_userInpt[1]){
            g_last_userInpt[0] == g_last_userInpt[2];
            g_count = 1;
        }else if(g_last_userInpt[1] == g_last_userInpt[2]){
            g_last_userInpt[0] = g_last_userInpt[2];
            g_count = 2;
        }else{
            g_count = 0;
            printf("Let's start over.");
        }
    }else{
        g_count++;
    }
}

//END file normalization.c

