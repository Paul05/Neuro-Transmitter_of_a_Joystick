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

#define LASTINPUTMEMSIZE 3

int g_count = 0;
char g_last_userInpt[LASTINPUTMEMSIZE];


/**
 * This function checks to see if the inputted key is in the key mapping for
 * the wheel chair controller and neuro-input device. If it is a mapped key,
 * it returns 1 otherwise it returns 0.
 * @param key to validate is in the mapping for movement
 * @return 1 for true and 0 for false
 */
int aKey(const char key)
{
    int returnVal = 0;

    if(key == extG_controllerForwardCmd){
        returnVal = 1;
    }else if(key == extG_controllerBackCmd){
        returnVal = 1;
    }else if(key == extG_controllerLeftCmd){
        returnVal = 1;
    }else if(key == extG_controllerRightCmd){
        returnVal = 1;
    }else if (key == extG_controllerTestCmd){
        returnVal = 1;
    }else if(key == extG_controllerExitCmd){
        returnVal = 1;
    }else{
        returnVal = 0;
    }

    return returnVal;
    
} //end aKey function


/**
 * This function normalizes input and uses a global array and global count value.
 * The array holds the last several inputs which this function compares the
 * current inputted character to. This function then decides to send
 * the inputted character to the wheelchair controller or not, based on the
 * conditional statements below.
 *
 * @param toSendToController the current char that has been inputted to be
 *                          sent to the wheelchair controller
 */
void normalizationAlgorithm(const char toSendToController)
{
    if(g_count == 0)
    {
        g_last_userInpt[0] = toSendToController;
    }else if(g_count == 1)
    {
        g_last_userInpt[1] = toSendToController;
    }else if(g_count == 2)
    {
        g_last_userInpt[2] = toSendToController;
    }
    
    if(g_last_userInpt[0] == g_last_userInpt[1] && g_last_userInpt[0] == g_last_userInpt[2])
    {
        sendToWheelChairController(toSendToController);
        delayProgram(500);
        g_count = 2;
    }
    else if(!isnan(g_last_userInpt[2]))
    {
        if(g_last_userInpt[1] == g_last_userInpt[2])
        {
            g_last_userInpt[0] = g_last_userInpt[2];
            g_count = 2;
        }else
        {
            g_last_userInpt[0] = g_last_userInpt[2];
            g_count = 1;
        }
    }
    else
    {
        g_count++;
    }
    
} //end normalizationAlgorithm function


/**
 * This function decides tp hands off functionality to the appropriate
 * normalization/direction function based on if an inputted char is in the
 * current mapping. If not, the value is extraneous.
 * 
 * @param key a char that needs to be checked and if mapped needs to be normalized. 
 */
void callNormalizeDirectionFuncs(const char key)
{
    if(aKey(key))
    { //confirms if the key is one of your default keys
        normalizationAlgorithm(key); //normalizes the input
    }else
    {
        printf("\n*Error char not recognized! Char input: %c. \n\n", key); //char not recognized print error, will keep going though
    }//end switch on key
    
} //end callNormalizeDirectionFuncs function

//END file normalization.c
