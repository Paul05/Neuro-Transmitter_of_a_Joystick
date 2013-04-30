/*
* File: testMain.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*        Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Function: Unit tests for the code found in main.c under src.
*
* Created: Spring, 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "../src/main.h"

/**
 * Unit test for performMenuActionTest
 * @return 1 for success and 0 for failure
 */
int performMenuActionTest(void)
{
    char positiveNumbers[] = "01278";
    char negativeNumbers[] = {"9-110"};
    int portTest = 9600;
    int i;
	int result = 1;
    int resultFlag = 1;

    printf("Testing performMenuAction... \n");

    for(i=0; i < 5; i++)
    {	
    //    result = performMenuAction(positiveNumbers[i], &portTest, "TESTPORT"); //Commented out for differing main issue

        if (result < 1)
        {
            resultFlag = 0;
            printf("\n\t***Failure: didn't recieve expected positive return value!***\n");
            break;
        }
    }

    if ( result > 0)
    {
        for(i=0; i < 3; i++)
        {
			
  //          result = performMenuAction(negativeNumbers[i], &portTest, "TESTPORT"); //Commented out for differing main issue

            if (result > 0)
            {
                resultFlag = 0;
                printf("\n\t***Failure: didn't recieve expected negative return value!***\n");
                break;
            }
        }
    }

    printf("\nFinished testing perforMenuAction function\n");

    return resultFlag;

} //end test for performMenuAction


/**
* This function runs the suite of tests above.
* @return 1 for success and 0 for failure
*/
int testMain(void)
{
    int success;

    printf("Testing main.c... \n");
    success = performMenuActionTest();

    printf("\nmain.c suite finished: ");

    if (success == 1)
    {
        printf("success!\n");
    }
    else
    {
        printf("failure!\n");
    }

    return success;
       
} //testMain

//END File testMain.c
