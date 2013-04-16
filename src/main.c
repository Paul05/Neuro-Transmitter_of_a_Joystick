/*
* File: main.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*         Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Inputs: The program will show a menu so that the user can select different
*         options. The user will be able to set most input and output commands
*         as well as most serial port options.
*
* Function: This program sets up communication with the Arduino. The
*           connection may be USB, but this program uses serial as typical
*           Arduino behavior is to mimic a serial port and communication.
*           If the test completes and communication works, then this program
*           takes inputs from the keyboard. Defaults are: t is reserved for testing
*           and x is reserved for exiting. w is forward, s is back, d is right,
*           and a is left. This is designed to be inputed from various neuro
*           EEG headsets. They do this via their proprietary and other open software write
*           a char to the keyboard based on a brain activity or muscular face action.
*
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
#include "usbSerialComm.h"
#include "userInput.h"
#include "neuroInputSetup.h"
#include "normalization.h"

#define DYNAMICTESTCMD "dynamicTest"  //command for valgrind to dynamic test the code

/**
* Welcome message function that displays a welcome message on the console.
*/
void welcomeMessage(void)
{
    printf("\nWelcome to the 'Neuro-Transmitter Of A Joystick' Group's "
            "Emotiv Normalization Program 1.0!\n\n");

} //end welcomeMessage


/**
* Exit message function that displays an exit message and keeps console open
* until any key is pressed on the keyboard.
*
*/
void exitMessage(void)
{
    printf("\n\nGoodbye\n\n");
    printf("\n\nPlease press 'ENTER' to exit.\n\n\n");
    fflush(stdout); //need to flush stdout before using getchar
    (void)getchar(); //keeps console open until user presses key on keyboard

}//end exitMessage


/**
 * Prints user instructions to the screen.
 */
void showUserInstructionMessage(void)
{
    printf("\n\tMake sure the neuro(EEG) headset is connected and that the software"
    " inputs to this program.\n\tActions for forward, back, left, and right,"
    " must be translated to keyboard inputs into this \n\tprogram via your headset "
    "software.\n\tDefaults are: w is forward, s is back, a is left, and d is right.\n"
    "\n\tAlso, make sure the Arduino or other wheelchair/joystick controller is "
    "connected and \n\tcommunicating through a Serial port.\n\tYou will need to "
    "know the name of the port that it is connected on, as well as the baud rate "
    "\n\tof the connection. "
    "This controller must accept string inputs from that serial connection.\n\n\t"
    "If that is all done, this program will normalize inputs from your EEG,\n\t"
    "and communicate with the wheelchair.\n\n\t"
    "Enjoy!\n\n");
    
}//end showUserInstructionMessage


/**
 * Shows the user a menu to select various program options
 */
void showMenu()
{
    printf("\nOptions Menu:\n\n"
           " 0 - Help\n"
        //   " 1 - View Current Setup Configuration\n"
        //   " 2 - Load Previously Saved Setup File\n"
        //   " 3 - Save Setup Changes to a File\n"
           " 4 - Change Serial Port Name\n"
           " 5 - Change Serial Port Baud Rate\n"
       //    " 6 - Change Neuro/Controller Input Commands\n"
           " 7 - Start Neuro-Control of the Wheelchair\n\n"
           " 8 - Exit the program\n\n"
           "Selection: \n\n"
           );
    
}//end showMenu function


/**
 * This function contains the switch statement that calls the responsible
 * functions for performing the actions listed in the showMenu function above.
 * Those actions are selectable by the user.
 * @param actionNumberFromUser integer that corresponds to menu function in showMenu
 * @return integer for success (>=1 = success, <=0 = failure).
 */
int performMenuAction(int actionNumberFromUser, char portName[])
{
    int flagToReturn = 1;

    switch ( actionNumberFromUser )
    {
        case 0:
            showUserInstructionMessage();
            break;
        case 1:
            //TODO Show setup configuration
            break;
        case 2:
            //TODO Load previous setup file
            break;
        case 3:
            //TODO Save setup file
            break;
        case 4:
            flagToReturn = getPortName(portName);
            break;
        case 5:
            flagToReturn = getBaudRate();
            break;
        case 6:
            //TODO Change Input Cmds here
            break;
        case 7:
            flagToReturn = 2; //go to neuro-input loop
            break;
        case 8:
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
    int baudRate = 0;
    int successFlag = 0;
    char neuroHeadSetInput = '\0';
    int menuInput;

    welcomeMessage();

    if ( argc == 2 && (strcasecmp(argv[1],DYNAMICTESTCMD) == 0) ) //check test mode from cmd line
    {
        printf("\n**Dynamic Analysis Testing Mode Enabled.** \n\n");
        //DO Dynamic test mode here (call functions)
        successFlag = 2;
    }
    else if (argc > 1)
    {
        printf("\nWarning! Improper command argument or number of command arguments "
                "detected.\n\tThis program does not use command line arguments as input.\n\n");
    }
    else
    {        
        do
        {
            successFlag = 0;
            menuInput = '9';

            showMenu();
            getInput(menuInput);
            fflush(stdout); 
//            menuInput = getchar();
            (void)getchar(); //remove enter TODO Bad Way fix with userInput function

            successFlag = performMenuAction(menuInput, portName);

            if (successFlag >= LWRBAUDRATE)
            {
                baudRate = successFlag;
                successFlag = 1;
            }         

            if (successFlag == 2)
            {
                printf("\n\nSetting up communication with Arduino on port: %s at rate %i... \n\n", portName, baudRate);
               
                successFlag = setupCommunication(portName, baudRate);

                if (successFlag > 0)
                {
                    successFlag = testControllerCommunication(); //test communication with arduino
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
                        neuroHeadSetInput = getCharConsole();

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
