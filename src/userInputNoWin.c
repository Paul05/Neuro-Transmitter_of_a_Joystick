/*
 * File:   userInputNoWin.c
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
 * Note: This file is for Unix, Linux, or Mac operating systems only.
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "userInput.h"
#include "usbSerialComm.h"


/**
 * This function is designed to get a port name from the user on the console.
 * Return: It returns a -1 if the user wishes to exit, 0 for failure and
 *          1 for success.
 * Furthermore, the inputed string (as a parameter to this function)
 * will be returned to the calling function.
 * Note: It should be reasonably free of improper and extraneous
 *          input unless the input line is longer than the buffer.
 */
int getPortName(char outPortName[])
{    
    char inputLine[BUFFERLENGTH];  //this is used as buffer for raw user input
    int errorFlag;     //status of input 1 = error keep going, 0 = stop success
    int length;    //var for length of buffer returned    

    do
    {
        errorFlag = 0;
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
                return -1; //user wishes to exit
            }
            else if ( strncmp(inputLine,"COM",3) == 0 ) //check if portname conforms to beginning "COM"
            {
                if ( strlen(inputLine) == STDPORTLENGTH-1 ) //if ports 1-9
                {
                    strncpy(outPortName,inputLine,STDPORTLENGTH); //put the inputLine into outPortName but not more than STDPORTLENGTH
                    return 1;
                }
                else if (strlen(inputLine) == LRGERPORTLENGTH-1) //if ports 10+
                {
                    strncpy(outPortName,DEVICENAMEAPPEND,strlen(DEVICENAMEAPPEND));  //put device(close to DOS) name into string first
                    strncat(outPortName,inputLine,LRGERPORTLENGTH);  //concate device name header with port name since windows needs this for ports 10+
                    return 1;
                }
                //fall through to generic warning
            }
            else
            {
                printf("\n*Error in port name being entered. "
                        "Make sure it's the proper length and format. \n\t"
                        "Example: 'COM1' or type 'exit' to end the program. \n\n");
                errorFlag = 1; //too many strings entered or too long or improper format.
            }
        }
        else
        {
            printf("\n*Error in port name being entered. \n\t*Please try again or "
                    "type 'exit' to end the program.\n\n");
            errorFlag = 1; //usually no input found (blank)
        }

    }while(errorFlag == 1); //end loop get port name

    return 0; //return failure if fall through
    
} //end getPortName function


/**
 * This function is designed to get the baud rate from the user
 * and reduces erroneous and extraneous input within reason.
 * Return: It returns a -1 if the user wishes to exit, 0
 *          for failure and above 1 for success.
 * Note: It should be reasonably free of improper
 *          input unless the input line is longer than the buffer.
 */
int getBaudRate(void)
{
    char inputLine[BUFFERLENGTH];  //this is used as buffer for raw user input    
    int length;    //var for length of buffer returned
    int outBaudRate; //int for baud rate and status of input 1 = error or keep going,
    
    do
    {
        outBaudRate = 1;
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
                return -1; //user wishes to exit
            }
            else if (1 == sscanf(inputLine, "%d", &outBaudRate))  //int is found
            {
                if (outBaudRate < LWRBAUDRATE || outBaudRate > UPPRBAUDRATE ) //check upper and lower possible baud rate bounds
                {
                    printf("*Please enter a valid baud rate. "
                            "(9600 is default) \n\n");
                    outBaudRate = 1; //baud rate is invalid
                }
                else
                {
                    return outBaudRate; //baud rate is valid success return it
                }
            }
            else
            {
                printf("\n*Please enter one number for the baud rate of "
                        "the connection. \n\t*Example: '9600'. \n\n");
                outBaudRate = 1; //too many ints entered etc.
            }
        }
        else
        {
            printf("\n*Error in baud rate entered. Please try again or "
                    "type 'exit' to end the program.\n\n");
            outBaudRate = 1; //improper input (probably blank)
        }

    }while(outBaudRate == 1); //end loop get baud rate

    return 0; //fall through return 0 for neutral failure

} //end getBaudRate function


/**
 * This function gets a single character (without pressing enter after)
 *   from the console and returns it.
 * Returns: Single char from console input.
 * Note: This is not reasonably free of improper input. It is excepted to be so,
 *          since a machine would be entering data at the point this function
 *          is used.
 * Warning: This function is platform dependent to certain compilers and
 *          environments.
 *
 */
char getCharConsole(void)
{  
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	
	return ch;  
   
}//end function getCharConsole

//END file userInputNoWin.c
