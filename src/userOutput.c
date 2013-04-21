/*
 * File:   userOutput.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This file contains functions that output data or prompts to the user.
 *
 *  * Created Spring, 2013
 */

#include <stdio.h>

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
void showMenu(void)
{
    printf("\nOptions Menu:\n\n"
           " 0 - Help\n"
           " 1 - View Current Setup Configuration\n"
        //   " 2 - Load Previously Saved Setup File\n"
        //   " 3 - Save Setup Changes to a File\n"
           " 4 - Change Serial Port Name\n"
           " 5 - Change Serial Port Baud Rate\n"
       //    " 6 - Change Neuro/Controller Input Commands\n"
           " 7 - Start Neuro-Control of the Wheelchair\n\n"
           " 8 - Exit the program\n\n"
           "Selection: "
           );

}//end showMenu function


/**
 *
 */
void showSetupConfiguration(void)
{

}//end showConfiguration function

//END file userOutput.c.
