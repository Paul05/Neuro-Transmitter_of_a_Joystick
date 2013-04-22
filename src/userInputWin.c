/*
 * File:   userInputWin.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This file contains functions to get user input from the console.
 *  The functions in order: get a string port name, an integer baud rate, as
 *  well as a character, all from the console. The port name and baud rate
 *  handle limited error checking and limited bound checking for those inputs
 *  with constants defined in usbSerialComm.h. 
 *
 * Note: This file is for Windows only as it uses conio.h and specific function(s) and port names for Windows.
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "userInput.h"
#include "usbSerialComm.h"


/**
 * This function is designed to get a port name from the user on the console.
 *  The input array will hold the portname if this function completes successfully.
 * Return: It returns a -1 if the user wishes to exit, and
 *          1 for success.
 * Furthermore, the inputed string (as a parameter to this function)
 * will be returned to the calling function.
 * Note: It should be reasonably free of improper and extraneous
 *          input unless the input line is longer than the buffer.
 *
 * @param outPortName string port to be inputted from user
 */
int getPortName(char outPortName[])
{    
    char inputLine[BUFFERLENGTH];  //this is used as buffer for raw user input
    int returnFlag;
    int length;    //var for length of buffer returned

    do
    {
        returnFlag = 0;
        printf("\nPlease enter the port name the Arduino is connected on: ");

        if (fgets(inputLine, sizeof(inputLine), stdin))
        {
            length = strlen(inputLine);  //get length of input

            if (inputLine[length-1] == '\n')
            {
                inputLine[length-1] = 0; //replace newline fgets puts in
            }

            if (strcasecmp(inputLine,USEREXITCOMMAND) == 0)  //compare ignore case
            {  
                returnFlag = -1; //user wishes to exit
            }
            else if ( strncmp(inputLine,"COM",3) == 0 ) //check if portname conforms to beginning "COM"
            {
                if ( strlen(inputLine) == STDPORTLENGTH-1 ) //if ports 1-9
                {
                    strncpy(outPortName,inputLine,STDPORTLENGTH); //put the inputLine into outPortName but not more than STDPORTLENGTH
                    returnFlag = 1;
                }
                else if (strlen(inputLine) == LRGERPORTLENGTH-1) //if ports 10+
                {
                    strncpy(outPortName,DEVICENAMEAPPEND,strlen(DEVICENAMEAPPEND));  //put device(close to DOS) name into string first
                    strncat(outPortName,inputLine,LRGERPORTLENGTH);  //concate device name header with port name since windows needs this for ports 10+
                    returnFlag = 1;
                }
                //fall through to generic warning
            }
            else
            {
                printf("\n*Error in port name being entered. "
                        "Make sure it's the proper length and format. \n\t"
                        "Example: 'COM1' or type 'exit' to end the program. \n\n");
                returnFlag = 0; //too many strings entered or too long or improper format.
            }
        }
        else
        {
            printf("\n*Error in port name being entered. \n\t*Please try again or "
                    "type 'exit' to end the program.\n\n");
            returnFlag = 0; //usually no input found (blank)
        }

    }while(returnFlag == 0); //end loop get port name

    return returnFlag; //return failure if fall through
    
} //end getPortName function


/**
 * This function is designed to get the baud rate from the user
 * and reduces erroneous and extraneous input within reason.
 * Return: It returns a -1 if the user wishes to exit and above 1 for success.
 * Note: It should be reasonably free of improper
 *          input unless the input line is longer than the buffer.
 */
int getBaudRate(void)
{
    char inputLine[BUFFERLENGTH];  //this is used as buffer for raw user input
    int returnFlag;
    int length;    //var for length of buffer returned
    
    do
    {
        returnFlag = 0;
        printf("\nPlease enter the baud rate of the connection to "
                "the Arduino: ");

        if (fgets(inputLine, sizeof(inputLine), stdin))
        {          
            length = strlen(inputLine); //get length of input

            if (inputLine[length-1] == '\n')
            {
                inputLine[length-1] = 0; //replace newline fgets puts in
            }

            if (strcasecmp(inputLine,USEREXITCOMMAND) == 0)  //compare ignore case
            {
                returnFlag = -1; //user wishes to exit
            }
            else if (1 == sscanf(inputLine, "%d", &returnFlag))  //int is found
            {
                if (returnFlag < LWRBAUDRATE || returnFlag > UPPRBAUDRATE ) //check upper and lower possible baud rate bounds
                {
                    printf("*Please enter a valid baud rate. "
                            "(9600 is default) \n\n");
                    returnFlag = 0; //baud rate is invalid
                }                
            }
            else
            {
                printf("\n*Please enter one number for the baud rate of "
                        "the connection. \n\t*Example: '9600'. \n\n");
                returnFlag = 0; //too many ints entered etc.
            }
        }
        else
        {
            printf("\n*Error in baud rate entered. Please try again or "
                    "type 'exit' to end the program.\n\n");
            returnFlag = 0; //improper input (probably blank)
        }

    }while(returnFlag == 0); //end loop get baud rate

    return returnFlag; //fall through return 0 for neutral failure

} //end getBaudRate function


/**
 * This function gets a single character (without pressing enter after)
 *   from the console and returns it.
 * Returns: Single char from console input.
 * Note: This is not reasonably free of improper input. It is excepted to be so,
 *          for speed and more data will come later to correct invalid input.
 * Warning: This function is platform dependent to certain compilers and
 *          environments due to the getch function which needs to be in conio.h.
 *          and is usually only found on Windows systems.
 * @return char from console
 */
char getCharNoEnter(void)
{    
    return getch(); //call to getchar to get char without enter being pressed
    //This is done for speed and not to use a custom keyboard library.  
}//end function getCharNoEnter


/**
 * This function gets a single character (user presses enter after)
 *    from the console and returns it.
 * Returns: Single char input from the user.
 * @return char from console
 */
char getCharWithEnter(void)
{
    char inputLine[BUFFERLENGTH];  //this is used as buffer for raw user input
    char returnFlag;
    int length;   //var for length of buffer returned
    
    do
    {
        returnFlag = -1;
        
        if (fgets(inputLine, sizeof(inputLine), stdin))
        {
            length = strlen(inputLine); //get length of input
            
            if (inputLine[length-1] == '\n')
            {
                inputLine[length-1] = 0; //replace newline fgets puts in
            }
            
            if (strcasecmp(inputLine,USEREXITCOMMAND) == 0)  //compare ignore case
            {
                returnFlag = -2; //user wishes to exit
            }
            else if ( 1 != sscanf(inputLine, "%c", &returnFlag) )  //char is found
            {                
               returnFlag = -1; //too many ints entered etc.
            }  
        }       
        
    }while(returnFlag == -1); //end loop get user's numerical input for the menu
    
    return returnFlag; 

} //end getCharWithEnter function

//END file userInputWin.c
