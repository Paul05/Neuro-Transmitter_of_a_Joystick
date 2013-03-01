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
 * to provide a better user experience.
 *
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include "left.h"
#include "right.h"
#include "forward.h"
#include "usbSerialComm.h"



/**
 * Welcome message function that displays a welcome message on the console.
 */
void welcomeMessage(void)
{
    printf("Welcome to the 'Neuro-Trasmitter Of A Joystick' Group's "
            "Emotiv Normalization Program 1.0!\n\n");
}


/**
 * Exit message function that displays exit message and keeps console open
 * until key is pressed on keyboard.
 */
void exitMessage(void)
{
    printf("\n\nGoodbye\n\n");
    printf("\n\nPlease press 'ENTER' to exit.\n\n\n");
    fflush(stdout);
    (void)getchar();
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
    int baudRate = 0;
    char* serialPortName;

    welcomeMessage();

    if (argc != 2)
    {
        printf("\nImproper number of command line arguments!\n");
        printf("\tUsage: NeuroControlProgram.exe Port BaudRate\n");
        exitMessage();
        return(EXIT_FAILURE);
    }
    else
    {
        serialPortName = argv[1];
        baudRate = atoi(argv[2]);
    }

    

    left();
    right();
    forward();
    usbSerialComm();

    exitMessage();
    return (EXIT_SUCCESS);
 
} //end main

//END File main.c
