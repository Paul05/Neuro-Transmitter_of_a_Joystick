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
 * The below method checks to see if the input key is a default key you have.
 * If it is, it returns true else it returns false.
 */
int aKey(char key){
    int theVal = 0;
    if(key == extG_controllerForwardCmd){
        theVal = 1;
    }else if(key == extG_controllerBackCmd){
        theVal = 1;
    }else if(key == extG_controllerLeftCmd){
        theVal = 1;
    }else if(key == extG_controllerRightCmd){
        theVal = 1;
    }else if (key == extG_controllerTestCmd){
        theVal = 1;
    }else if(key == extG_controllerExitCmd){
        theVal = 1;
    }else{
        theVal = 0;
    }
    return theVal;
}
/*
 * The below method goes through a rigorous if/else loop that checks the inputs.
 * If the last three inputs are the same it will send it to the arduino and reset.
 * If they were not the same, it sets the values in appropriate places and tries again.
 */
void normalizationAlgorithm(char toSend){
    if(g_count == 0){
        g_last_userInpt[0] = toSend;
    }else if(g_count == 1){
        g_last_userInpt[1] = toSend;
    }else if(g_count == 2){
        g_last_userInpt[2] = toSend;
    }
    
    if(g_last_userInpt[0] == g_last_userInpt[1] && g_last_userInpt[0] == g_last_userInpt[2]){
        sendToWheelChairController(toSend);
        delayProgram(400);
        g_count = 2;
    }else if(!isnan(g_last_userInpt[2])){
        if(g_last_userInpt[1] == g_last_userInpt[2]){
            g_last_userInpt[0] = g_last_userInpt[2];
            g_count = 2;
        }else{
            g_last_userInpt[0] = g_last_userInpt[2];
            g_count = 1;
        }
    }else{
        g_count++;
    }
}

/*
 * This function hands off functionality to the appropriate normalization/direction
 * functions based on an inputted char.
 * @param char key
 */
void callNormalizeDirectionFuncs(char key)
{
    if(aKey(key)){ //confirms if the key is one of your default keys
        normalizationAlgorithm(key); //normalizes the input
    }else{
        printf("\n*Error char not recognized! Char input: %c. \n\n", key); //char not recognized print error, will keep going though
    }//end switch on key
    
} //end callNormalizeDirectionFuncs function

