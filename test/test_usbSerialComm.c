/*
* File: test_usbSerialComm.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*        Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Function: Unit tests for the code found in usbSerialComm.c under src.
*
* Created: Spring, 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "../src/usbSerialComm.h"

/**
 * Unit test for setBaudRate function
 * @return 1 for success and 0 for failure
 */
int setBaudRateTest(void)
{
	int validBaudRates[] = {110,300,600,1200,2400,4800,9600,14400,19200,38400,57600,115200,128000,256000};
	int invalidBaudRates[] = {-1,-110,-109,-256000,-256001,-255999,0,1,109,256001,10000000};
	int validBaudRateSize = 14;
	int invalidBaudRateSize = 11;
    int index;
	int result = 1;
    int resultFlag = 1;

    printf("\n\tTesting setBaudRate... \n");

    for(index=0; index < validBaudRateSize; index++)
    {	
        result = setBaudRate(validBaudRates[index]);

        if (result < 1)
        {
            resultFlag = 0;
            printf("\n\t\t***Failure: didn't recieve expected positive return value!***\n");
            break;
        }
    }

    if ( result > 0)
    {
        for(index=0; index < invalidBaudRateSize; index++)
        {
			
			result = setBaudRate(invalidBaudRates[index]);

            if (result > 0)
            {
                resultFlag = 0;
                printf("\n\t\t***Failure: didn't recieve expected negative return value!***\n");
                break;
            }
        }
    }

    printf("\n\tFinished testing setBaudRate function\n");

    return resultFlag;

} //end test for performMenuAction


/**
* This function runs the suite of tests above.
* @return 1 for success and 0 for failure
*/
int testUsbSerialComm(void)
{
    int success;

    printf("\nTesting usbSerialComm.c... \n");
    success = setBaudRateTest();

    printf("\nusbSerialComm.c suite finished: ");

    if (success == 1)
    {
        printf("success!\n\n");
    }
    else
    {
        printf("failure!\n\n");
    }

    return success;
       
} //end testUsbSerialComm function

//END File test_usbSerialComm.c