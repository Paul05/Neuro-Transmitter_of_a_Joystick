/*
* File: main.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*        Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Input: The program will show a menu so that users can select different
*        options. All user information is inputted and communicated through
*        the console.
*
* Function: This program sets up communication with a wheelchair controller. The
*           connection may be USB or serial but the USB must mimic a serial port
*           and communication.
*           If the connection is setup successfully, this program will then
*           take inputs from the keyboard. 
*           Default inputs are: t is reserved for testing and x is reserved
*           for exiting.
*           w is forward, s is back, d is right, and a is left.
*           Those last movement inputs are designed to be inputted from a "Neuro"
*           EEG/EMG headset. They may do this via their proprietary and/or
*           other open software. The goal is to map an action on the headset to
*           a designated keyboard character.
*           This program then sends that input to the wheelchair controller
*           after it normalizes the input to provide a consistent and usable
*           user experience. This version is in its infancy and is based on the
*           the Emotiv EPOC headset and its nuances. 
*
* Created: Spring, 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "userInput.h"
#include "userOutput.h"
#include "usbSerialComm.h"
#include "neuroInputSetup.h"
#include "normalization.h"
#include "configFileIO.h"

#define DYNAMICTESTCMD "dynamicTest"  //command for valgrind to dynamic test the code

int baudRate = 0; //Making baudRate a global variable so that it can be passed to then 


/**
 * This function is for dynamic testing of the program. This is designed so an 
 * outside testing tool can adequetely test most of the various functions.
 * As testing the normal paths of this program would need a simulated serial port, 
 * and simulated input device, which is not available in our limited test server or scenarios.
 */
void dynamicTestFunction(void)
{
    

} //end dynamicTestFunction

/**
 * This function contains the switch statement that calls the responsible
 * functions for performing the actions listed in the showMenu function.
 * Those actions are selectable by the user. This provides a main menu
 * that is the main user interface with this program.
 * @param actionNumberFromUser char that corresponds to menu function in showMenu
 * @param portName string for the name of the serial port joystick conroller is connected on
 * @return integer for success (>=1 = success, <=0 = failure).
 */
int performMenuAction(char actionNumberFromUser, char portName[])
{
    int flagToReturn = 1;

    switch ( actionNumberFromUser )
    {
        case '0':
            showUserInstructionMessage();
            break;
        case '1':
            showSetupConfiguration(baudRate, portName);
            break;
        case '2':
            baudRate = inputFile();
            showSetupConfiguration(baudRate, portName);
            break;
        case '3':
            outputFile(baudRate);
            break;
        case '4':
            flagToReturn = getPortName(portName);
            break;
        case '5':
            flagToReturn = getBaudRate(); 
            break;
        case '6':
            changeMovementCommands(); //change neuro-input cmds
            break;
        case '7':
            flagToReturn = 2; //go to neuro-input loop (control wheelchair)
            break;
        case '8':
            flagToReturn = -2; //exit
            break;
        default:
            printf("Unrecognized option selected. Number entered: %c. Please try again!\n",
                    actionNumberFromUser);
            flagToReturn = -1;
            break;
    } //end switch case for integer actions in the menu

    return flagToReturn;

} //end performMenuAction function


/**
* This is the Main function that 'runs' the program.
* @param argc
* @param argv
* @return
*/
int main(int argc, char** argv)
{
    char portName[LRGERPORTLENGTH+3]; //+3 for margin of error
    int successFlag = 0;
    char neuroHeadSetInput = '\0';
    int menuInput;

    welcomeMessage();
    

    if ( argc == 2 && (strcasecmp(argv[1],DYNAMICTESTCMD) == 0) ) //check test mode from cmd line
    {
        printf("\n**Dynamic Analysis Testing Mode Enabled.** \n\n");
        dynamicTestFunction();
        successFlag = 2;
    }
    else if (argc > 1)
    {
        printf("\nWarning! Improper command argument or number of command arguments "
                "detected.\n\tThis program does not use command line arguments as input.\n\n");
    }
    else
    {
        if(checkFile()){
            baudRate = inputFile();
            showSetupConfiguration(baudRate, portName);
        }
        
        do
        {
            successFlag = 0;
            showMenu();
            menuInput = getCharWithEnter();
 
            successFlag = performMenuAction(menuInput, portName);

            if (successFlag >= LWRBAUDRATE)
            {
                baudRate = successFlag;
                successFlag = 1;
            }         

            if (successFlag == 2)
            {
                printf("\n\nSetting up communication with the WheelChair Controller "
                        "on port: %s at rate %i... \n\n", portName, baudRate);
               
                successFlag = setupCommunication(portName, baudRate);

                if (successFlag > 0)
                {
                    successFlag = testControllerCommunication(); //test communication with controller
                }

                if (successFlag > 0)
                {
                    testWheelChairOperation(); //test movement of wheelchair briefly
                }

                if (successFlag > 0)
                {
                    changeMovementCommands();
                    printf("\nProgram ready for Neuro-Headset Input and Control of a Wheelchair! \n\n");
                    printf("\tCommands are:   Forward= %c.  Back= %c.  Left= %c.  Right= %c  and Exit= %c. \n\n",
                            extG_controllerForwardCmd, extG_controllerBackCmd,
                            extG_controllerLeftCmd, extG_controllerRightCmd, extG_controllerExitCmd );

                    do
                    {
                        neuroHeadSetInput = getCharNoEnter();

                        printf("\n(DEBUG PURPOSES ONLY) Char recieved: %c. \n\n",neuroHeadSetInput); //TODO: Remove this, for debug purposes only!

                        callNormalizeDirectionFuncs(neuroHeadSetInput);  //Call respective direction/normalization functions based on input

                    } while( neuroHeadSetInput != extG_controllerExitCmd); //end loop get input from console from emotiv device


                    if ( tolower(neuroHeadSetInput) == extG_controllerExitCmd)
                    {
                        printf("\nExit character found! Now exiting the program. \n\n");
                    }
                    else
                    {
                        printf("\nUnexpected character or action found! Char found: %c. "
                                "Now Exiting!\n\n", neuroHeadSetInput);
                    }
                } //end if check setup complete and if so run loop to get input from neuro-headset and output to controller

          } //end if else check if inputs completed and setup communications/test communications

        }while(successFlag >= -1); //end do while loop until user selects exit in menu
        
    } //end if/else check cmd line for test mode, if not prompt user as normal

    exitMessage();
    closeCommunication(); 

    if (successFlag == -2)
    {      
        return (EXIT_SUCCESS);
    }
    else
    {        
        return(EXIT_FAILURE); 
    }

} //end main

//END File main.c
