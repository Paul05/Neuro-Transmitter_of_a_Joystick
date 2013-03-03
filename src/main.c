/* 
 * File:   main.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Main takes two inputs the first is the name of the serial port the
 *    Arduino is connected to and the next is the baud rate for the connection/
 *    Standard baud rate is 9600.
 *
 * This program then takes inputs from the keyboard (wasd) or others depending on
 * specifications and sends that input to the Arduino after it normalizes the input
 * to provide a consistent and usable user experience for an Emotiv controlled
 * wheelchair.
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include "left.h"
#include "right.h"
#include "forward.h"
#include "usbSerialComm.h"


#define BUFFERLENGTH 128    //arbitrary size picked as standar input buffer length
#define STDPORTLENGTH 5    //size of the standard 1-9 com ports plus null
#define LRGERPORTLENGTH 6    //size of 10+ com ports plus null
#define DEVICENAMEAPPEND "\\\\.\\"   //device or "DOS" name for serial port (this is backslashed for C, regular is: '\\.\COMXX'
#define USEREXITCOMMAND "exit"   //string the user is to type to exit out of input loops/program
#define LWRBAUDRATE 110      //lower possible baud rate
#define UPPRBAUDRATE 256000  //upper possible baud rate 


/**
 * Welcome message function that displays a welcome message on the console.
 */
void welcomeMessage(void)
{
    printf("Welcome to the 'Neuro-Trasmitter Of A Joystick' Group's "
            "Emotiv Normalization Program 1.0!\n\n");

} //end welcomeMessage


/**
 * Exit message function that displays exit message and keeps console open
 * until key is pressed on keyboard.
 */
void exitMessage(void)
{
    printf("\n\nGoodbye\n\n");
    printf("\n\nPlease press 'ENTER' to exit.\n\n\n");
    fflush(stdout);     //need to flush stdout before using getchar
    (void)getchar();    //keeps console open until user presses key on keyboard

}//end exitMessage


/**
 * If the portName and baudRate are not specified on the command line,
 * this function will get those values from the user and try to get the
 * correct input within reason. It returns a -1 if the user wishes to exit, 0
 * for failure and 1 for success. Furthrmore, the input parameters of the string
 * and int are designed to be returned to the calling function.
 */
int handleUserInput(char outPortName[], int *outBaudRate)
{
    //TODO Refactor into new file (Create file and header)
    char inputLine[BUFFERLENGTH];  //this is used as buffer for raw user input   
    int errorFlag;     //status of input 1 = error keep going, 0 = stop success
    int length;    //var for length of buffer returned

    do
    {
        errorFlag = 0;
        printf("\nPlease enter the port name to connect with the Arduino: ");

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
            else if ( strlen(inputLine) == STDPORTLENGTH ) //if ports 1-9
            {
                //TODO Error Here See if length correct!!!
                printf("OutputRawSTD= %s.\n", inputLine);
                strncpy(outPortName,inputLine,STDPORTLENGTH);
                 printf("OutputSTD= %s.\n", outPortName);

            }
            else if (strlen(inputLine) == LRGERPORTLENGTH) //if ports 10+
            {
                printf("OutputRawLRG= %s.\n", inputLine);
                strncpy(outPortName,DEVICENAMEAPPEND,strlen(DEVICENAMEAPPEND));
                strncat(outPortName,inputLine,LRGERPORTLENGTH);
                printf("OutputLRG= %s. \n", outPortName);
            }          
            else
            {
                printf("\n*Please enter one string for the port being used by "
                        "the arduino of the proper length. "
                        "\n\t*Example: 'COM1'. \n\n");
                errorFlag = 1; //too many strings entered or too long etc.
            }
        }
        else
        {
            printf("\n*Error in port name being entered. \n\t*Please try again or "
                    "type 'exit' to end the program.\n\n");
            errorFlag = 1; //usually no input found (blank)
        }

    }while(errorFlag == 1); //end loop get port name

    do
    {
        errorFlag = 1;
        printf("\nPlease enter the intended baud rate of the connection to "
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
                printf("Output Baud Rate= %d. \n", outBaudRate);

                if (*outBaudRate < LWRBAUDRATE || *outBaudRate > UPPRBAUDRATE ) //check upper and lower possible baud rate bounds
                {
                    printf("*Please enter a valid baud rate. "
                            "(9600 is default) \n\n");
                    errorFlag = 1; //baud rate is invalid
                }
                else
                {
                    return 1; //baud rate is valid success
                }
            }
            else
            {
                printf("\n*Please enter one number for the baud rate of "
                        "the connection. \n\t*Example: '9600'. \n\n");
                errorFlag = 1; //too many ints entered etc.
            }
        }
        else
        {
            printf("\n*Error in baud rate entered. Please try again or "
                    "type 'exit' to end the program.\n\n");
            errorFlag = 1; //improper input (probably blank)
        }

    }while(errorFlag == 1); //end loop get baud rate

    return 0; //fall through return (in this case) a neutral number

} //end handleUserInput


/**
 * This is the Main function that calls other functions and 'runs' the program.
 * It needs two arguments on the command line.
 * First is serial port name (string) and the next is the baud rate (integer -
 *   9600 is standard).
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
    int successFlag = 0;
    char portName[13];
    int  baudRate;

    welcomeMessage();

    if (argc < 2)
    {
       successFlag = handleUserInput(portName, &baudRate); //inputs not on cmd line ask user
    }
    else
    {
        if (strlen(argv[1]) == LRGERPORTLENGTH)
        {
            strncpy(portName,DEVICENAMEAPPEND,7); //
            strncat(portName,argv[1],strlen(argv[1]));
        }
        else if ( strlen(argv[1]) == STDPORTLENGTH )
        {
            strncpy(portName,argv[1],strlen(argv[1]));
        }
        else
        {
            printf("Warning invalid port name in: %s \n", argv[1]);
            exitMessage();
            return(EXIT_FAILURE);
        }
    }

    if (successFlag == -1 || successFlag == 0)
    {
        exitMessage();
        return(EXIT_FAILURE);
    }


    //setupSuccessFlag = setupCommunication(argv[1],atoi(argv[2]));
    printf("Setting up communication with Arduino on port: %s at rate %s... \n", portName, baudRate);

    left();
    right();
    forward();
    

    exitMessage();
    return (EXIT_SUCCESS);
 
} //end main

//END File main.c
