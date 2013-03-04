/* 
 * File:   main.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Inputs: Main takes two inputs the first is the name of the serial port the
 *    Arduino is connected to and the next is the baud rate for the connection/
 *    Standard baud rate is 9600. If not found on the cmd line, the program will
 *    ask the user to enter those values with more error checking.
 *
 * This program then sets up communication via serial to an arduino. The
 * connection may in fact be USB but this program uses serial as Arduino
 * uses USB but mimics a serial port and communication. If the tests complete
 * and communication works, then this program takes inputs from the keyboard
 * (wasd) or others depending on specifications.
 * It then sends that input to the Arduino after it normalizes the input
 * to provide a consistent and usable user experience for an Emotiv controlled
 * wheelchair. In essence the Emotiv program will use "keystrokes" to communicate
 * with the Arduino after normalization and the Arduino will convert the input
 * into usable turning and movement instructions which trip various relays on
 * an electric wheelchair.
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include "usbSerialComm.h"
#include "userInput.h"
#include "left.h"
#include "right.h"
#include "forward.h"


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
 *
 * Note: Is platform specific and uses getchar()!
 * 
 */
void exitMessage(void)
{
    printf("\n\nGoodbye\n\n");
    printf("\n\nPlease press 'ENTER' to exit.\n\n\n");
    fflush(stdout);     //need to flush stdout before using getchar
    (void)getchar();    //keeps console open until user presses key on keyboard

}//end exitMessage

/*
 *This is the switch statement to send the signal to go left or right.
 */
void motor_func(char key){ 
    switch (key) {
            /*
             * The commented out code below would only be uncommented if we
             * plan to implement going forward/backward with mind instead of
             * just left/right.
             */
//        case 'w':
//            goForward();
//            break;
//        case 's': 
//            goBack();
//            break;
        case 'a':
            goLeft();
            break;
        case 'd':
            goRight();
            break;
    }
}



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
    char portName[13];
    int  baudRate = 0;
    int successFlag = 0;
    char emotivInput = '\0';

    welcomeMessage();

    if (argc < 2)
    {
       successFlag = getPortName(portName); //inputs not on cmd line ask user

       if (successFlag == 1)
       {
            baudRate = getBaudRate(); //ask user for baud rate
            successFlag = baudRate; //checks user input back from getBaudRate()
       }
    }
    else
    {
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
            printf("Warning invalid port name in: %s \n", argv[1]); //portname not correct length or otherwise invalid
            successFlag = 0;

        } //end if else get values from cmd line

    } //end if else check cmd args or get user input


    if (successFlag < 1) //functions to get input from user failed or user wished to exit
    {
        exitMessage(); //exit message
        return(EXIT_FAILURE); //exit program with failure
    }
    else
    {
        printf("\nSetting up communication with Arduino on port: %s at rate %i... \n\n", portName, baudRate);
       
        successFlag = setupCommunication(portName, baudRate); //setup communications with arduino
        
        if (successFlag > 0) 
        {
            successFlag = testCommunication(); //test communications with arduino
        }

        if (successFlag > 0)
        {
            sendIntToArduino(2);     //Test Actual Movement (Wheelchair turns left then right for example, test functions etc.)
            //delay
            sendIntToArduino(3);
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
        printf("\nProgram ready and in loop for Emotiv Input or press 'x' to exit! \n\n");

        do
        {
            emotivInput = getCharConsole(); //get input from console

            printf("\n(REMOVE) Char recieved: %c. \n\n",emotivInput);

            //Switch Statement

        } while( emotivInput != 'x' && emotivInput != 'X' ); //end loop get input from console from emotiv device


        if ( tolower(emotivInput) == 'x' )
        {
            printf("\nExit character found now exiting the program! \n\n");
        }
        else
        {
            printf("\nUnexpected character or action found! Last char: %c. "
                    "Now Exiting!\n\n", emotivInput);
        }
        
        successFlag = closeCommunication();
        exitMessage();
        return (EXIT_SUCCESS);
        
    } //end if else check tests complete and perform get input and normalization loop
 
} //end main

//END File main.c
