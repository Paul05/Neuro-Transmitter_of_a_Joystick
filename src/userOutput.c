/*
 * File:   userOutput.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This file contains functions that output informative text
 *          or input prompts to the user.
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include "usbSerialComm.h"

/**
* Welcome message function that displays a welcome message on the console.
*/
void welcomeMessage(void)
{
    printf("\nWelcome to the 'Neuro-Transmitter Of A Joystick' Group's "
            "Emotiv Normalization Program 1.0!\n\n");

} //end welcomeMessage


/**
* Exit message function that displays an exit message and keeps the console open
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
 * Prints program specific instructions to the screen.
 */
void showUserInstructionMessage(void)
{
    printf(
    "\n\n\n\n\tMake sure the neuro(EEG) headset is connected and that it's software"
    " inputs to this program.\n\tActions for forward, back, left, and right,"
    " must be translated to keyboard inputs into this \n\tprogram via your headset "
    "software.\n\n\tDefaults are: w forward, s back, a left, and d right.\n"

    "\n\tAlso, make sure the Arduino or other wheelchair/joystick controller is "
    "connected and \n\tcommunicating through a Serial Port connection."
    "\n\tYou will need to know the name of the port that it is connected on, "
    "as well as the baud rate \n\tof the connection. "

    "This controller must accept string inputs from that serial connection.\n\n\t"
    "If that is all done, this program will normalize inputs from your EEG headset"
    ",\n\tand communicate them to the wheelchair/joystick controller.\n\t"
    "At that point, you will be able to control the wheelchair with actions"
    "\n\tmapped from your neuro-headset software."
            
    "\n\n\t*If you have any issues inside of the program you can type "
    "'exit' or 'x' \n\tand the program will stop."
    "\n\n\t*Furthermore, a disconnect button on the wheelchair controller "
    "\n\tor other reset button should halt all wheelchair movement."
    "\n\n\t*Finally, while this program does accept input from your headset device, "
    "\n\tyou can always manually override with the keyboard on the computer "
    "running this program."
            
    "\n\n\tThanks for using our software and enjoy!\n\n"
    );

}//end showUserInstructionMessage


/**
 * Shows the user a menu to select various program options
 */
void showMenu(void)
{
    printf("\n\nOptions Menu:\n\n"
           " 0 - Help\n"
           " 1 - View Current Setup Configuration\n"
           " 2 - Load Previously Saved Setup File\n"
           " 3 - Save Setup Changes to a File\n"
           " 4 - Change Serial Port Name\n"
           " 5 - Change Serial Port Baud Rate\n"
           " 6 - Change Neuro-Headset and WheelChair Controller Commands\n"
           " 7 - Start Neuro-Control of the Wheelchair\n\n"
           " 8 - Create Testing Log File\n"
           " 9 - Exit the program\n\n"
           "Selection: "
           );

}//end showMenu function


/**
 * Shows the user the current setup configuration.
 */
void showSetupConfiguration(const int baudRate, const char portName[])
{
    printf(
           "\n\n\n"
           "*****Your current setup is as follows: *****\n\n"
           "\nWheelchair Controller Connection Port: %s"
           "\nWheelchair Controller Connection Baud Rate: %d"
           "\nForward Command: %c"
           "\nBackward Command: %c"
           "\nLeft Command: %c"
           "\nRight Command: %c"
           "\nExit Command: %c"
           "\n\n\n*****        End Setup Display        *****\n\n\n",
                portName, baudRate,
                extG_controllerForwardCmd, extG_controllerBackCmd,
                extG_controllerLeftCmd, extG_controllerRightCmd,
                extG_controllerExitCmd
            );

}//end showConfiguration function

//END file userOutput.c.
