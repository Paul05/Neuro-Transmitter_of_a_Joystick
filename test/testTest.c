/*
 * File:   testTest.c   
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Test our unit test auto-run startup.
 *  
 * Note: 
 *
 * Created Spring, 2013
 */

#include <stdio.h>
#include <stdlib.h>
//#include "../src/usbSerialComm.h"


void test1() {
    printf("Test 1\n");
}

void test2() {
    printf("Test 2\n");
    printf("%%TEST_FAILED%% time=0 testname=test2 \n");
}

int main(int argc, char** argv) 
{    
	printf("\nWelcome to the 'Neuro-Transmitter Of A Joystick' Group's "
            "\n\tAuto-Unit Test Program for our Emotiv Normalization Program!\n\n");
	printf("%%SUITE_STARTING%%\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 )\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 ) \n");

    printf("%%TEST_STARTED%% test2 )\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

//END file testTest.c