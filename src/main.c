/*
* File: main.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*         Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Inputs: The program will ask the user to enter two inputs. The first is
*         the name of the serial port the Arduino is connected on and the next
*         input is the baud rate for that connection. Typical port names start
*         with COM such as (COM1) for example. Standard baud rate is 9600 with
*         typical Arduinos, but can be changed in the Arduino code.
*
* Function: This program sets up communication with the Arduino. The
*           connection may be USB, but this program uses serial as typical
*           Arduino behavior is to mimic a serial port and communication.
*           If the test completes and communication works, then this program
*           takes inputs from the keyboard (wasd). t is reserved for testing
*           and x is reserved for exiting. w is forward, s is back, d is right,
*           and a is left. This is designed to be inputed from various neuro
*           EEG headsets that can via their proprietary and other software write
*           a char to the keyboard based on a brain or muscular face action.
*
*           This program then sends that input to the Arduino
*           after it normalizes the input to provide a consistent and usable
*           user experience. This version is in its infancy and is based on the
*           the Emotiv EPOC headset and its nuances. The Arduino will convert
*           the input (chars) or "strings" sent on the serial port into usable
*           turning and movement commands to an electric wheelchair in the four
*           standard directions.
*
* Created: Spring, 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usbSerialComm.h"
#include "userInput.h"
#include "left.h"
#include "right.h"
#include "forward.h"

#define DEVTESTCMD "test"
char arduinoForward = 'w';
char arduinoBack = 's';
char arduinoRight = 'd';
char arduinoLeft = 'a';
char arduinoExit = 'x';

/**
* Welcome message function that displays a welcome message on the console.
*/
void welcomeMessage(void)
{
    printf("Welcome to the 'Neuro-Trasmitter Of A Joystick' Group's "
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
 * Prints to the screen instructions for the user on how to properly use
 * this program with an EEG headset and an Arduino.
 */
void userInstructionMessage(void)
{
    printf("\nMake sure the neuro(EEG) headset is connected and that the software"
    "points to this program. \n Actions for forward, back, left, and right,"
    "must be translated to keyboard inputs to this program via your headset "
    "software.\nCurrently w is forward, s is back, a is left, and d is right.\n"
    "\nAlso, make sure the Arduino or other slave controller that is hooked up"
    "to the wheelchair is connected and acting as a Serial port.\n You need to "
    "know the name of the port (starts with COM and then a number). \n The Arduino"
    "or other slave controller must accept char inputs on the serial connection "
    "the same as what was described above. \n If that is all done, this program"
    "will normalize inputs from your EEG and communicate with the wheelchair. \n\n"
    "Enjoy!  \n\n");
    
}//end userInstructionMessage


/*
 * This function hands off functionality to the appropriate normalization/direction
 * functions based on an inputted char.
 * @param char key 
 */
void callNormalizeDirectionFuncs(char key)
{
    switch (key)
    {       
        case arduinoForward:
            goForward();
            break;
        case arduinoBack:
            goBackward();
            break;
        case arduinoLeft:
            goLeft();
            break;
        case arduinoRight:
            goRight();
            break;
        case 't': case 'T':
            printf("*Test char recieved (t). Now testing communication with the Arduino... \n\n"); //TODO do we want to test movement or comms?
            break;
        case arduinoExit:
            printf("*Exit char recieved %c. \n\n", arduinoExit);
            //exit command found, fall through (after this function) needs to take care of the actual exit
            break;
        default:                   
            printf("\n*Error char not recognized! Char input: %c. \n\n", key); //char not recognized print error, will keep going though
            break;
    } //end switch on key
} //end callNormalizeDirectionFuncs function


/**
* This is the Main function that calls other functions and 'runs' the program.
* It needs two arguments on the command line.
* First is serial port name (string) and the next is the baud rate (integer -
* 9600 is standard).
* @param argc
* @param argv
* @return
*/
int main(int argc, char** argv)
{
    char portName[13];
    int baudRate = 0;
    int successFlag = 0;
    char emotivInput = '\0';

    welcomeMessage(); //let user know what they just executed
    userInstructionMessage(); //inform the user how to use the program
  
    if (argc < 3)
    { 
       if (strcasecmp(argv[1],DEVTESTCMD) == 0) //see if cmd is same as cmd for dev test mode ignore case
       {
           printf("\n**Secret Developer Testing Mode Enabled.** \n\n");
           successFlag = 1000;
       }
       else
       {
           successFlag = getPortName(portName); //inputs not on cmd line ask user

           if (successFlag == 1)
           {
                baudRate = getBaudRate(); //ask user for baud rate
                successFlag = baudRate; //checks user input back from getBaudRate()
           }
       } //end if/else check for dev mode
    }
    else
    {
        successFlag = 2; //set flag for success since is set below only on failure
        
        if (strlen(argv[1]) == LRGERPORTLENGTH)
        {
            strncpy(portName,DEVICENAMEAPPEND,strlen(DEVICENAMEAPPEND)); //put device name header first
            strncat(portName,argv[1],strlen(argv[1])); //append port name to make complete device name
        }
        else if ( strlen(argv[1]) == STDPORTLENGTH )
        {
            strncpy(portName,argv[1],strlen(argv[1])); //put the cmd arg into the portName var
        }
        else
        {
            printf("\n*Warning invalid port name on cmd line. Port entered: %s. \n\n",
                    argv[1]); //portname not correct length or otherwise invalid
            successFlag = 0;

        } //end if else get port name from cmd line

        baudRate = atoi(argv[2]); //convert cmd line arg string into int and store in baudRate

        if (baudRate < LWRBAUDRATE || baudRate > UPPRBAUDRATE ) //check upper and lower possible baud rate bounds
        {
            printf("\n*Warning invalid baud rate on cmd line. Rate entered: %i. \n\n",
                    baudRate);
            successFlag = 0; //baud rate is invalid
        } //end if check baud rate from cmd line

    } //end if else get user input or take from cmd line 


    if (successFlag < 1) //functions to get input from user failed or user wished to exit
    {
        exitMessage(); //exit message
        return(EXIT_FAILURE); //exit program with failure
    }
    else if (successFlag != 1000) //not in test mode
    {
        printf("\n\nSetting up communication with Arduino on port: %s at rate %i... \n\n", portName, baudRate);
       
        successFlag = setupCommunication(portName, baudRate); //setup communications with arduino
        
        if (successFlag > 0)
        {
            successFlag = testCommunication(); //test communications with arduino
        }

        if (successFlag > 0)
        {            
            testOperation(); //tests everything is working correctly with predefined test pattern
        }
        
    } //end if else check if inputs completed and setup communications/test communications


    if (successFlag < 1)
    {
        successFlag = closeCommunication();
        exitMessage();
        return(EXIT_SUCCESS);
    }
    else
    {
        changeKeys();
        printf("\nProgram ready and in loop for Emotiv Input or press %c to exit! \n\n", arduinoExit);

        do
        {
            emotivInput = getCharConsole(); //get input from console

            printf("\n(DEBUG PURPOSES ONLY) Char recieved: %c. \n\n",emotivInput); //TODO: Remove this, for debug purposes only!
           
            callNormalizeDirectionFuncs(emotivInput);  //Call respective direction/normalization functions based on input

        } while( emotivInput != arduinoExit); //end loop get input from console from emotiv device


        if ( tolower(emotivInput) == arduinoExit)
        {
            printf("\nExit character found! Now exiting the program. \n\n");
        }
        else
        {
            printf("\nUnexpected character or action found! Char found: %c. "
                    "Now Exiting!\n\n", emotivInput);
        }
        
        successFlag = closeCommunication();
        exitMessage();
        return (EXIT_SUCCESS);
        
    } //end if else check tests complete and perform get input and function call loop
 
} //end main

//END File main.c
