/* 
 * File:   main.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Alg to smooth inputs. *
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include "left.h"
#include "right.h"
#include "forward.h"
#include "usbSerialComm.h"

int main(int argc, char** argv)
{
    printf("This is the neuro-transmitter group's project!\n\n");

    left();
    right();
    forward();
    usbSerialComm();

    printf("\nGoodbye!\n\n");

	printf("\n\nPlease press 'ENTER' to exit.\n\n\n");
	fflush(stdout);
	(void)getchar();
	
    return (EXIT_SUCCESS);
} //end main

//END File main.c
