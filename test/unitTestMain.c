/*
* File: unitTestMain.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*        Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Function: Automatically unit tests the code found in src and gives output
*           as to pass or failure. 
*
* Created: Spring, 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "testMain.h"
#include "testNormalization.h"
#include "testConfigFileIO.h"


/**
* This is the Main function that 'runs' the test program.
* @param argc
* @param argv
* @return
*/
int main(int argc, char** argv)
{
    printf("\nWelcome to the 'Neuro-Transmitter Of A Joystick' Group's "
            "\n\tAuto-Unit Test Program for our Emotiv Normalization Program!\n\n");

    //testMain();   //Commented out due to test integration, doesn't work after put into the suite (two mains), was used for testing and function has not changed.
    testNormalization();
//    testMystrsep(); //Commented out due to ant build errors.
		
	
	printf("\n\nPlease press 'ENTER' to exit.\n\n\n");
    fflush(stdout); //need to flush stdout before using getchar
    (void)getchar(); //keeps console open until user presses key on keyboard	
    return (EXIT_SUCCESS);   
} //end main

//END File unitTestMain.c
